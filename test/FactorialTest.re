open TestFramework;
open Library.Factorial;

describe("factorial", ({test}) => {
  test("factorial(0) should equal 1", ({expect}) => {
    let result = factorial(0);

    expect.int(result).toBe(1);
  });
  test("factorial(1) should equal 1", ({expect}) => {
    let result = factorial(1);

    expect.int(result).toBe(1);
  });
  test("factorial(6) should equal 720", ({expect}) => {
    let result = factorial(6);

    expect.int(result).toBe(720);
  });
  test("factorial(-1) should throw", ({expect}) => {
    expect.fn(() => factorial(-1)).toThrow()
  });
});


