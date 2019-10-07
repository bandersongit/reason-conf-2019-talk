open Library.User;
open TestFramework;

describe("user test without builder", ({test}) => {
  test("fullName", ({expect}) => {
    let user = {
      firstName: "Ben",
      lastName: "Anderson",
      email: "Banderson@example.com",
      isLoggedIn: true,
    };

    let fullName = getFullName(user);

    expect.string(fullName).toEqual("Ben Anderson");
  })
});

open UserBuilder;

describe("user test with builder", ({test}) => {
  test("fullName", ({expect}) => {
    /* arrange */
    let user =
      userBuilder
      |> withFirstName("Ben")
      |> withLastName("Anderson")
      |> build;

    /* act */
    let fullName = getFullName(user);

    /* assert */
    expect.string(fullName).toEqual("Ben Anderson");
  })
});


