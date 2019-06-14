import numpy as np
import matplotlib.pyplot as plt
import imageio


print("Running SegmentedLeastSquare Visualizer....")
fileName1 = "input.txt"
fileName2 = "output.txt"

with open(fileName1) as f:
    lines = f.readlines()

points = []
for line in lines:
    points.append(list(map(float, line.split())))
points = points[1:]

xmin = float("inf")
xmax = float("-inf")    
for point in points:
    if point[0]<xmin:
        xmin = point[0]
    if point[0]>xmax:
        xmax = point[0]

x1 = []
y1 = []
for i in range(0, len(points)):
    x1.append(points[i][0])
    y1.append(points[i][1])


fig, ax = plt.subplots(figsize=(5,5))

ax.scatter(x1, y1, marker='o', s=15, color='b')


gif = []


fig.canvas.draw()
image = np.frombuffer(fig.canvas.tostring_rgb(), dtype='uint8')
gif.append(image.reshape(fig.canvas.get_width_height()[::-1] + (3,)))


f = open(fileName2, "r")
for p in range(100):
    line = ""
    line = f.readline()
    flag = 0
    final1 = []
    final2 = []
    temp = []
    fig, ax = plt.subplots(figsize=(5,5))
    ax.scatter(x1, y1, marker='o', s=15, color='b')

    print(p)
    while line != "\n":
        line = f.readline()
        if flag==1:
            if line=='$\n':
                final2.append([temp[0][0], temp[-1][0]])
                temp.clear()
            else:
                temp.append(list(map(float, line.split())))
        else:
            if line=='$\n':
                flag=1
            else:
                final1.append(list(map(float, line.split())))

    for i in range(0, len(final1)):
        x = np.linspace(final2[i][0],final2[i][1],100)
        y = (final1[i][0])*x + final1[i][1]
        ax.plot(x, y, color='r')

    #plt.show()
    ax.set_title("Cost = "+str(p+1))
    fig.canvas.draw()
    image = np.frombuffer(fig.canvas.tostring_rgb(), dtype='uint8')
    gif.append(image.reshape(fig.canvas.get_width_height()[::-1] + (3,)))

imageio.mimsave('./linefitting.gif', gif, fps=2)