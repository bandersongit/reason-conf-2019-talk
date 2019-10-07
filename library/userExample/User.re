type t = {
    firstName: string,
    lastName: string,
    email: string,
    isLoggedIn: bool
}

let getFullName = (user) => String.concat(" ", [user.firstName, user.lastName])
