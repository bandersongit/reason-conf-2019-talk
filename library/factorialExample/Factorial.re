let rec factorial = n => {
  switch (n) {
  | n when n == 0 => 1
  | n when n < 0 =>
    raise(
      Invalid_argument(
        Printf.sprintf(
          "Factorial is only defined for non-negative integers, received %d",
          n,
        ),
      ),
    )
  | _ => n * factorial(n - 1)
  };
};
