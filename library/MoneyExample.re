type usd;
type euro;

type currency('a) =
  | USD: currency(usd)
  | Euro: currency(euro);

type money('a) = {
  amount: float,
  currency: currency('a),
};

let add: type a. (money(a), money(a)) => money(a) =
  (amount1, amount2) => {
    currency: amount1.currency,
    amount: amount1.amount +. amount2.amount,
  };

let convert: type a b. (money(a), currency(b)) => money(b) =
  (money, currency) => {
    switch (money.currency, currency) {
    | (USD, USD) => money
    | (USD, Euro) => {...money, currency: Euro}
    | (Euro, USD) => {...money, currency: USD}
    | (Euro, Euro) => money
    };
  };

let oneDollar = {amount: 1., currency: USD};
let oneEuro = {amount: 1., currency: Euro};

add(oneDollar, convert(oneEuro, USD));
/* add(oneDollar, oneEuro) */
