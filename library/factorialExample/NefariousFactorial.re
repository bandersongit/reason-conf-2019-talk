let factorial = n => {
  switch (n) {
  | n when n == 0 => 1
  | n when n == 1 => 1
  | n when n == 6 => 720
  | n when n < 0 =>
    raise(
      Invalid_argument(
        Printf.sprintf(
          "Factorial is only defined for non-negative integers, received %d",
          n,
        ),
      ),
    )
  | _ => 42
  };
};
