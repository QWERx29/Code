import turtle
import random
import math

screen = turtle.Screen()
screen.setup(1000, 800)
screen.bgcolor("black")
screen.title("随机射线星图生成器")
screen.tracer(0)  

artist = turtle.Turtle()
artist.hideturtle()
artist.speed(0)  

drawn_positions = []

def randcolor():
    r = random.random()
    g = random.random()
    b = random.random()
    return (r, g, b)

def is_too_close(x, y, min_distance=80):
    for pos in drawn_positions:
        dx = pos[0] - x
        dy = pos[1] - y
        distance = math.sqrt(dx**2 + dy**2)
        if distance < min_distance:
            return True
    return False

def draw_star(x, y, size, rays, color, width):
    artist.penup()
    artist.goto(x, y)
    artist.pendown()
    
    artist.color(color)
    artist.pensize(width)
    
    angle = 360 / rays
    for _ in range(rays):
        artist.forward(size)
        artist.backward(size)
        artist.right(angle)

def generate_star():
    while True:
        x = random.randint(-450, 450)
        y = random.randint(-350, 350)
        
        if not is_too_close(x, y):
            drawn_positions.append((x, y))
            break
    size = random.randint(20, 150)
    rays = random.randint(5, 30)
    color = randcolor()
    width = random.randint(1, 5)
    return x, y, size, rays, color, width

for _ in range(25):
    params = generate_star()
    draw_star(*params)

turtle.mainloop()