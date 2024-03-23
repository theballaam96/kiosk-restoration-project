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

uploaded = {
    ROM_US: [False, "cf806ff2603640a748fca5026ded28802f1f4a50", None],
    ROM_KS: [False, "b4717e602f07ca9be0d4822813c658cd8b99f993", None],
}

def build():
    FINISH_MESSAGE = tk.Label(app, text="Building hack, please wait...", fg="white")
    FINISH_MESSAGE.grid(row=4, column=0, columnspan=2)
    FINISH_MESSAGE.configure(background=BACKGROUND_COLOR)
    subprocess.run(["build.bat"])
    FINISH_MESSAGE.configure(text="ROM has been built to ./rom/dk64-kioskrestoration-dev.z64")

def show(label_row, label_column, copyname):
    filename = askopenfilename()
    if not os.path.exists("rom/"):
        os.mkdir("rom/")
    if uploaded[copyname][2] is not None:
        uploaded[copyname][2].destroy()
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
    output_text = "Valid" if valid_rom else "Invalid"
    output_color = "white" if valid_rom else "red"
    local_label = tk.Label(app, text=output_text, fg=output_color)
    local_label.grid(row=label_row, column=label_column)
    local_label.config(background=BACKGROUND_COLOR)
    uploaded[copyname][2] = local_label
    uploaded[copyname][0] = valid_rom
    for f in uploaded:
        if not uploaded[f][0]:
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
img_h = (128 * img_scale) + (2 * img_padding)
img_w = (224 * img_scale) + (2 * img_padding)
img_raw = Image.open("./assets/logo.png")
resized_img = img_raw.resize((img_raw.width * img_scale, img_raw.height * img_scale))
canvas = tk.Canvas(app, width=img_w, height=img_h, highlightthickness=0, highlightbackground=BACKGROUND_COLOR)
img = ImageTk.PhotoImage(resized_img)
canvas.create_image(img_padding, img_padding, anchor=tk.NW, image=img)
canvas.configure(background=BACKGROUND_COLOR)
canvas.grid(column=0, row=0, columnspan=2)

# US
BUTTON_US = tk.Button(app, text="Upload US ROM", command=lambda: show(1, 1, ROM_US), fg="white")
BUTTON_US.grid(row=1, column=0)
BUTTON_US.configure(background=BUTTON_COLOR)

# Kiosk
BUTTON_KS = tk.Button(app, text="Upload Kiosk ROM", command=lambda: show(2, 1, ROM_KS), fg="white")
BUTTON_KS.grid(row=2, column=0)
BUTTON_KS.configure(background=BUTTON_COLOR)

subprocess.run(["python", "-m", "pip", "install", "-r", "requirements.txt"])

for child in app.winfo_children():
    child.grid_configure(padx=10, pady=10)
app.mainloop()