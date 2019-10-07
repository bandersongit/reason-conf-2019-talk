open TestFramework;

/* doesn't compile and that's the point ;) */
/* let {describe} =
  describeConfig
  |> withLifecycle(testLifecycle =>
       testLifecycle
       |> afterEach(() => print_endline("after each"))
       |> beforeEach(() => print_endline("before each"))
     )
  |> build; */
