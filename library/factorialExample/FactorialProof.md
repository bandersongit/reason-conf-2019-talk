```reason
let rec factorial = (n) => {
    switch(n) {
      | n when n == 0 => 1
      | n when n < 0 => raise(Invalid_argument(Printf.sprintf("Factorial is only defined for non-negative integers, received %d", n)))
      | _ => n * factorial(n - 1)
    }
  };
```

We want to show factorial(n) = n! for all natural numbers n.

Base case n = 0

By substitution we have
```reason
    let factorial(0) = {
    switch(0) {
      | n when 0 == 0 => 1
      | n when 0 < 0 => raise(Invalid_argument(Printf.sprintf("Factorial is only defined for non-negative integers, received %d", 0)))
      | _ => 0 * factorial(n - 1)
    }
}
```
which evaluates to 1 = 0! from the first case of the pattern match.

Inductive Hypothesis: Suppose that factorial(n) = n! for some natural number n.

By substitution we have
```reason
    let factorial(n + 1) = {
    switch(0) {
      | n when n + 1 == 0 => 1
      | n when n + 1 < 0 => raise(Invalid_argument(Printf.sprintf("Factorial is only defined for non-negative integers, received %d", 0)))
      | _ => n + 1 * factorial(n + 1 - 1)
    }
}
```
Because n is a natural number, we know n + 1 > 0 so we fall back to the last match statement which reduces to n + 1 * factorial(n). By our inductive hypothesis this is equal to n + 1 * n!, which by definition is equal to (n + 1)!

[]

