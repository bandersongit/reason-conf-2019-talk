type userBuilder = {
  firstName: string,
  lastName: string,
  email: string,
  isLoggedIn: bool
};

let userBuilder = {
  firstName: "first",
  lastName: "last",
  email: "fake@example.com",
  isLoggedIn: true
};

let withFirstName = (firstName, userBuilder) => {...userBuilder, firstName};

let withLastName = (lastName, userBuilder) => {...userBuilder, lastName};

let withEmail = (email, userBuilder) => {...userBuilder, email};

let build: userBuilder => Library.User.t =
  builder => {
    firstName: builder.firstName,
    lastName: builder.lastName,
    email: builder.email,
    isLoggedIn: builder.isLoggedIn
  };

  
