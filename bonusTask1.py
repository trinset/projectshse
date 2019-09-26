from tkinter import *


# Here a window with some information, 2 chessboard cells and an entry box with a button are created

# The program shows the colors of the given cells and matches them, showing "=" if the colors are the same and "!="
# if the colors are different

# The input is 4 numbers with spaces between them. The first number is the coordinate of the first cell on x-axis,
# the second number is the coordinate of the first cell on y-axis, the third number is the coordinate of the second
# cell on x-axis and the fourth number is the coordinate of the second cell on y-axis




def getAnswer():
    a, b, c, d = list(map(int, entry1.get().split()))
    if ((a + b) % 2) == ((c + d) % 2):
        canvas.create_rectangle(200, 100, 300, 200, fill = "white", outline = '')
        canvas.create_text(253, 160, text="=", font=(None, 60))
        if (a + b) % 2:
            canvas.create_rectangle(40, 90, 190, 240, fill="white")
            canvas.create_rectangle(315, 90, 465, 240, fill="white")
        else:
            canvas.create_rectangle(40, 90, 190, 240, fill="black")
            canvas.create_rectangle(315, 90, 465, 240, fill="black")
    else:
        canvas.create_rectangle(200, 100, 300, 200, fill="white", outline='')
        canvas.create_text(253, 160, text="!=", font = (None, 60))
        if (a + b) % 2:
            canvas.create_rectangle(40, 90, 190, 240, fill="white")
        else:
            canvas.create_rectangle(40, 90, 190, 240, fill="black")
        if (c + d) % 2:
            canvas.create_rectangle(315, 90, 465, 240, fill="white")
        else:
            canvas.create_rectangle(315, 90, 465, 240, fill="black")

root = Tk()
canvas = Canvas(root, width = 500, height = 400)
canvas.pack()
canvas.create_rectangle(40, 90, 190, 240, fill = "dark gray")
canvas.create_rectangle(315, 90, 465, 240, fill = "dark gray")
canvas.create_rectangle(3, 3, 500, 62, fill = "light cyan")
canvas.create_text(10, 10, text = 'Info:', font = (None, 13), anchor = W)
canvas.create_text(10, 30, text = 'Contest Number: Second contest', font = (None, 13), anchor = W)
canvas.create_text(10, 50, text = 'Task: 10. Color of chessboard cells', font = (None, 13), anchor = W)
canvas.create_text(495, 10, text = 'Name: Vasyutin Oleg', font = (None, 13), anchor = E)
canvas.create_text(495, 30, text = "Input: Two cells (x1 y1 x2 y2)", font = (None, 13), anchor = E)
canvas.create_text(495, 50, text = "Output: Same color or not (= or !=)", font = (None, 13), anchor = E)
entry1 = Entry(root, font = (None, 22), width = 19)
canvas.create_window(253, 300, window=entry1)
button1 = Button(text='Enter', command=getAnswer, height = 2, width = 20, bg = 'brown')
canvas.create_window(253, 350, window=button1)
mainloop()