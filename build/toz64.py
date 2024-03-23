#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Copyright © 2019 Taylor C. Richberger <taywee@gmx.com>
# This code is released under the MIT license

import argparse
import shutil
from io import BytesIO

def convertchunk(chunk, byteswapped, wordswapped):
    '''Convert a chunk of 4 bytes, possibly byte swapping or word swapping (for
    16-bit bytes and 32-bit words).
    '''
    output = bytearray(chunk)

    if byteswapped:
        output[0], output[1] = output[1], output[0]
        output[2], output[3] = output[3], output[2]

    if wordswapped:
        # Don't use reversed because we want this fast and to stay a bytearray
        output[0], output[1], output[2], output[3] = output[3], output[2], output[1], output[0]

    return bytes(output)

def chunks(sequence, size):
    '''Yield sized chunks from a sequence.'''
    for offset in range(0, len(sequence), size):
        yield sequence[offset:offset + size]

def main():
    parser = argparse.ArgumentParser(description='Convert any N64 rom to z64 format')
    parser.add_argument('-V', '--version', action='version', version='0.1')
    parser.add_argument('-i', '--input', help="Input rom file", type=argparse.FileType('rb'), required=True)
    parser.add_argument('-o', '--output', help="Output z64 rom file", type=argparse.FileType('wb'), required=True)
    parser.add_argument('-v', '--verbose', help="Output extra information", action='store_true')
    args = parser.parse_args()

    with args.input as input:
        verbose = args.verbose

        magic = input.read(4)
        first = magic[0]

        if frozenset(magic) != frozenset((0x37, 0x12, 0x40, 0x80)):
            raise ValueError('Magic number does not match an expected n64 rom')

        byteswapped = first in bytes((0x37, 0x12))
        wordswapped = first in bytes((0x40, 0x12))

        lookup = {
            (False, False): 'z64',
            (True, False): 'v64',
            (False, True): 'n64',
            (True, True): 'v64+n64',
        }

        if verbose:
            print('Input format is {}'.format(lookup[(byteswapped, wordswapped)]))

        if byteswapped == False and wordswapped == False:
            if verbose:
                print('Simply copying {} to {}'.format(args.input.name, args.output.name))
            shutil.copy(args.input.name, args.output.name)
        else:
            with BytesIO() as output:
                output.write(convertchunk(
                    chunk=magic,
                    byteswapped=byteswapped,
                    wordswapped=wordswapped,
                ))
                fullinput = input.read()
                if verbose:
                    print('Converting all chunks')
                for chunk in chunks(fullinput, 4):
                    if len(chunk) != 4:
                        break
                    output.write(convertchunk(
                        chunk=chunk,
                        byteswapped=byteswapped,
                        wordswapped=wordswapped,
                    ))
                if verbose:
                    print('Writing output')
                with args.output as outfile:
                    outfile.write(output.getvalue())

        if verbose:
            print('Finished converting {} to {}'.format(args.input.name, args.output.name))

if __name__ == '__main__':
    main()