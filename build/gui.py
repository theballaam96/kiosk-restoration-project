import tkinter as tk
from tkinter.filedialog import askopenfilename
import os
import subprocess
import hashlib
from PIL import Image, ImageTk

# DO NOT RUN THIS FILE THROUGH gui.py
# RUN THE BATCH FILE INSTEAD

BACKGROUND_COLOR = "#0d1117"
BUTTON_COLOR = "#444444"

class App(tk.Frame):
    def __init__(self, parent):
        tk.Frame.__init__(self, parent)
        parent.geometry("500x450")
        parent.title("DK64 Kiosk Restoration Project")
        parent.configure(background=BACKGROUND_COLOR)
        self.grid_columnconfigure(0, weight=1)
        self.grid_columnconfigure(2, weight=1)
        self.configure(background=BACKGROUND_COLOR)

ROM_US = "dk64_us.z64"
ROM_KS = "dk64_kiosk.z64"
ROM_TEXT_US = "Upload US ROM"
ROM_TEXT_KS = "Upload Kiosk ROM"

uploaded = {
    ROM_US: [False, "cf806ff2603640a748fca5026ded28802f1f4a50", ROM_TEXT_US],
    ROM_KS: [False, "b4717e602f07ca9be0d4822813c658cd8b99f993", ROM_TEXT_KS],
}

def build():
    FINISH_MESSAGE = tk.Label(app, text="Building hack, please wait...", fg="white")
    FINISH_MESSAGE.grid(row=4, column=0, columnspan=2)
    FINISH_MESSAGE.configure(background=BACKGROUND_COLOR)
    subprocess.run(["build.bat"])
    FINISH_MESSAGE.configure(text="ROM has been built to ./rom/dk64-kioskrestoration-dev.z64")

BUTTON_BUILD = None

def show(button_item, copyname):
    global BUTTON_BUILD

    filename = askopenfilename()
    if not os.path.exists("rom/"):
        os.mkdir("rom/")
    print("CWD:", os.getcwd())
    print("File:", filename)
    output = f"rom/{copyname}"
    subprocess.run(["python", "./build/toz64.py", "-i", filename, "-o", output])
    sha1 = hashlib.sha1()
    valid_rom = False
    with open(output, "rb") as fh:
        data = fh.read()
        sha1.update(data)
    sha1_hex = sha1.hexdigest()
    if sha1_hex == uploaded[copyname][1]:
        valid_rom = True
    output_text = "✓" if valid_rom else "❌"
    output_color = "#07f01e" if valid_rom else "#ff0000"
    button_item.configure(text=f"{uploaded[copyname][2]} {output_text}", fg=output_color)
    uploaded[copyname][0] = valid_rom
    for f in uploaded:
        if not uploaded[f][0]:
            if BUTTON_BUILD is not None:
                BUTTON_BUILD.destroy()
            return
    BUTTON_BUILD = tk.Button(app, text="Build Hack", command=lambda: build(), fg="white")
    BUTTON_BUILD.grid(row=3, column=0, columnspan=2)
    BUTTON_BUILD.configure(background=BUTTON_COLOR)

app = tk.Tk()
App(app).grid(sticky="nsew")
app.grid_columnconfigure(0, weight=1)

# Logo
img_scale = 2
img_padding = 20
frame_padding = 0
img_h = (128 * img_scale) + (2 * img_padding)
img_w = (224 * img_scale) + (2 * img_padding)
img_raw = Image.open("./assets/logo.png")
resized_img = img_raw.resize((img_raw.width * img_scale, img_raw.height * img_scale))
canvas = tk.Canvas(app, width=img_w, height=img_h, highlightthickness=0, highlightbackground=BACKGROUND_COLOR)
img = ImageTk.PhotoImage(resized_img)
canvas.create_image(img_padding, img_padding, anchor=tk.NW, image=img)
canvas.configure(background=BACKGROUND_COLOR)
canvas.grid(column=0, row=0, columnspan=2)

# General Upload Frame
UPLOAD_FRAME = tk.Frame(app)
UPLOAD_FRAME.grid(row=1, column=0, columnspan=2)
UPLOAD_FRAME.configure(background=BACKGROUND_COLOR)

# US
BUTTON_US = None
BUTTON_US = tk.Button(UPLOAD_FRAME, text=ROM_TEXT_US, command=lambda: show(BUTTON_US, ROM_US), fg="white", padx=5)
BUTTON_US.grid(row=0, column=0)
BUTTON_US.configure(background=BUTTON_COLOR)

# Kiosk
BUTTON_KS = None
BUTTON_KS = tk.Button(UPLOAD_FRAME, text=ROM_TEXT_KS, command=lambda: show(BUTTON_KS, ROM_KS), fg="white", padx=5)
BUTTON_KS.grid(row=0, column=1)
BUTTON_KS.configure(background=BUTTON_COLOR)

subprocess.run(["python", "-m", "pip", "install", "-r", "requirements.txt"])

for child in app.winfo_children():
    child.grid_configure(padx=10, pady=10)
app.mainloop()