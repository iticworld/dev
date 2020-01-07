# BASIC DRAWING

## POINT

It represents a two dimension point, specified by its image coordinates x and y. We can define it as:

```c++
Point pt;
pt.x = 10;
pt.y = 8;
```

or

```c++
Point pt = Point(10, 8);
```

## SCALAR

- Represents a 4 element vector. The type Scalar is widely used in OpenCV for passing pixel values.
- In this tutorial, we will use it extensively to represent BGR values (3 parameters). It is not necessary to define the last argument if it is not going to be used.
- Let's see an example, if we are asked for a color argument and we give:

```c++
Scalar(a, b, c)
```

We would b defining a BGR color such as: Blue = a, Green = b and Red = c
