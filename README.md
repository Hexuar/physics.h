# Physics.h
Physics.h is a simple physics library introducing the "val" class, which represents a scalar, vector or matrix with a unit. For your convenience, the library is packaged in a single header. Simply include this and you're good to go.

## Usage
While physics values can be created with their constructor, you can also define them by multiplying a value with a unit. The entire library is under the **physics** namespace, and constants, as well as non SI units are under the **constants** and **units** namespaces respectively.

```CPP
val s = 2000 * M; // Values are defined by multiplying a number with a unit. This represents 2 km.
val t = 1.0_k * S; // SI suffixes can also be used to add exponents to your values.
val v = s / t; // Regular operations can be performed on physics values.

print(v); // We can print our result to the console using the print command.

val m = 0.52 * KG;
val F = m * g; // There are many constants included. This is the gravitational constant at sea level.

val h = 1.57_k * M;
val E = m * g * h;

print(F, E); // The print function can take any number of arguments.
```

It's also possible to use vectors and matrices, as demonstrated by the next example.
```CPP
val I = matrix({{1,2,3},{4,5,6},{7,8,9}}) * KG * (M^2); // Values are matrices, and can be initialised as such.
val omega = matrix({0.5,2.4,1.0}) * (S^-1); // Vectors are defined as 1xN or Nx1 matrices
val L = I * omega; // Vectors are automatically transposed in matrix multiplication

print(L);
```
