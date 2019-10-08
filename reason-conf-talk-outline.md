# Investing in Testing With Reason

I want you to come away from this talk with an understanding of the principles behind why we write tests and the ability to apply these principles in order to efficiently and effectively write software that will address your users’ needs. We will cover high level topics and a few specific strategies, some of which Reason is especially well suited to. However these ideas are by no means constrained to any particular programming language or paradigm.

## Why do we test?
 I believe the fundamental reason that we write tests is that we want to be confident that our code does what it says it does. We want this confidence because our goal is to solve the users’ problems and if our code doesn’t solve the users’ problems, we lose their trust and they will look for other solutions.

It is important to note that this confidence can come from other possible sources. If we want to be as confident as possible, then the gold standard is a formal mathematical proof. If we were to write formal proofs for our code we would have absolute confidence.

A type system in some ways offers a notion of “automated proof”. By this I don’t mean “if it compiles it works”, but I do mean that by making certain types of errors semantically impossible, we can be sure that they do not occur in our code. Understanding what your type system can offer in terms of guarantees and designing your types to reflect your business logic can go a long way towards building confidence in your code.


## Testing as a means of establishing confidence
> “Testing proves the presence of bugs, not the absence of bugs” - Edsger Dijkstra

It’s important to understand what tests can and cannot do. As opposed to formal proofs and the use of type checkers, testing provides empirical validation of highly specific scenarios. We are generally only demonstrating particular instances of a more general proposition that we would like to be true. To illustrate the difference between testing, proofs, and types, consider the factorial function.

You might recall from math class that this is a function that is defined recursively. 0! = 1, and n! = n * (n-1)!


```reason
let rec factorial = (n) => {
  switch(n) {
    | n when n == 0 => 1
    | n when n < 0 => raise(Invalid_argument(Printf.sprintf("Factorial is only defined for non-negative integers, received %d", n)))
    | _ => n * factorial(n - 1)
  }
};
```

We can formally prove the proposition `factorial(n) == n!` for all natural numbers using induction.

The Reason type system only tells us that factorial is of type `int => int`. It says nothing about the integers that are passed to or returned from the function, and it also doesn't reflect that we can fail with an exception.

In practice, we would probably write some unit tests that would look something like this
```reason
open TestFramework;

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
        let result = factorial(720);

        expect.int(result).toBe(720);
    });
    test("factorial(-1) should throw", ({expect}) => {
        expect.fn(() => factorial(-1)).toThrow();
    });
})
```

What this test suite proves is the exact set of propositions that we tested. It is easy to imagine another version of factorial that handles just these cases and then returns garbage for every other possible value.

So of the methods we tested, the proof showed that for all natural numbers, factorial(n) = n!. The type system said that if we return, we return an integer. The tests said that for 0, 1, and 6 factorial(n) = n!.

## So why don't we just prove everything?

The biggest problem with just proving everything, is cost. Proofs take time to write and verify. Additionally as they are based on the direct analysis of source code, they are difficult to maintain when the code changes as a change to the code generally means a change in the proof. 

That said formal proofs are currently employed extensively in academic papers and in embedded systems environments. Computer assisted proofs have helped make some breakthroughs in theoretical mathematics. The most famous example of this is the proof of the Four color theorem. I could see a day where we had some level of automatic proof generation or verification integrated into common industry practices. The good folks at Inria have a language/proof asistant called coq available as well that can interact with , Haskell, Scala, and ocaml (and hence also Reason). I haven't worked with it, but if you are interested in learning more, you should check it out.

## What if our types enforced our business logic?
Frameworks and languages go a long way to determining the amount of work needed to test your code as well. Stronger type guarantees can reduce the need for unit tests due to rendering certain types of errors (nulls) impossible out of the box. But we can do better still. You can strive to encode your high level business rules into the types you use in your application. By doing this, we are making the compiler dynamicalily prove that some properties that we care about hold!


## Money example

For example, consider the problem of operating on money. Money types typically has some amount associated with it, and, importantly, that amount is relative to a particular currency. We generally want to guarantee that when paying for something, or combining funds, that we are operating on quantities with the same currency. This is something that you might think to guard against with a precondition and unit tests, however with some intentional type design, we can make it so that erroneous code doesn’t even compile. Furthermore the guarantee we get here is *stronger* than the guarantee we get with the unit test. The unit test might say that we can’t add a dollar and a euro, the type annotation says that we can only add money of the same type.

## Rely lifecycle methods
This is a real example of this principle in practice. Like Jest, Rely has the beforeEach, afterEach, beforeAll, and afterAll lifecycle events. Unlike Jest, these functions can return values that can be later referenced in a safe way for user in tests and to perform teardown operations. Consequently, we need them to be called in a certain order. For example the return value of beforeEach is passed as an argument to afterEach, so we have this requirement that beforeEach must be called before afterEach. I encoded this requirement into the actual types of these functions using something called phantom types, and if you break this invariant, you actually get a compiler error that looks like this.

## On the value of testing

The software we write has constantly evolving demands which means that our code needs to grow and to change. This change is healthy, but we want to be able to maintain our confidence in spite of it.

Testing as a discipline can be an extremely efficient and effective means of establishing confidence in the face of evolving requirements and constant refactoring.

Tests can depend on higher level abstractions than formal proofs of correctness, and provide a more expressive way to describe desired behavior than can be reasonably accomplished with types alone in most scenarios.

Testing is a very broad subject and there are many different kinds of tests. Unit tests (which some people use to refer to all tests), integration tests, e2e tests, performance tests, service tests, and manual testing are just some examples.

Because there is so much complexity in the world of testing, and the relative value and costs vary so wildly by situation, it is important to understand how to analyze your unique situation. I am going to walk through the framework that I use when evaluating individual tests, thinking about how to test a system or feature, and when maintaining existing tests.

## A note on pyramids
Who here has seen this before?

This isn’t the framework I just alluded to, but I think it’s important to talk about because I find that this is one of the first things that come to mind when people think of testing. 

This is a heuristic that was first introduced by Mike Cohn in his book Succeeding with Agile which was published in 2009. The basic notion was that as you go higher up in the pyramid, tests became more expensive to write and more prone to breakage.

However these assumptions don't always hold. In recent years advances in UI technologies and testing frameworks have made UI/Integration/E2E testing cheaper than it has been before. 

### But what about unit tests?
Unit tests do certainly have their place. If I am writing a complex bit of logic, I will certainly write a unit test. However Reason and the functional style make it easier to not write tests in a lot of situations due to the prevalence of function composition and pattern matching. In general if test would look similar to the code I'm writing or I am confident that it is trivial, I skip the unit test. This does not necessarily mean sacrificing on code coverage, which I think is a flawed, but useful metric. I believe the goal should be that every piece of behavior or business rule should be specified in some kind of test. If we are adhering to this standard, code coverage should naturally be high, even without unit tests. Code coverage can give an approximation of this goal, but ultimately it is our responsibility to continuously make this kind of evaluation and encourage our teammates to do the same.


## Testing trophy
This is a more modern geometric representation of the testing hierarchy. KCD gave a talk at Assert(JS) entitled "Write tests. Not too many. Mostly integration". This title was borrowed on a 2016 tweet by Guillermo Rauch.

This testing shape reflects both the cheapening and the value of integration tests. There is also this bit at the bottom, which refers to the value is added by a static type system. In the context of Kent's talk and associated article, this is Flow, however Reason has quite a bit more to add in this regard.

## Cost vs. value
"Price is what you pay; value is what you get." - Warren Buffet

As for the rest of the pyramid, we have already established that the costs associated with different types of tests, are not constant. When assessing the efficacy of a particular test or set of tests, I look at what value is generated by the test or tests, and what the costs of them are in the specific context that I am dealing with.

Components:

* Value
    * relevance
    * diagnostic value
    * speed/automation

* Cost
    * Robustness (insensitivity to change)
    * Maintainability (If I have to make a change, how hard is it to do so?)
    * Upfront investment

Relevance - Am I testing things that matter? 
Diagnostic value - If there is a test failure, how confident am I that I can diagnose what is going on?
Speed/automation - Without this nothing else matters. If tests are fast I can run them more often and develop faster. Having a good CI pipeline ensures that tests are alway green.

Robustness - If I add a new feature, are these tests going to break? Are these tests flakey?
Maintainability - Clean code
Upfront investment - How much time is it going to take to add this test? Will writing this test make similar tests require less investment in the future?

## Relevance

We write software to solve problems for users. The thing we care about is that users are actually able to use the software as intended. That should be the highest priority at basically all times. Unit tests are great for ensuring that little pieces work, but it is the integration and e2e tests that make sure we are actually solving the problems we care about. Focusing on relevance also pays maintainability dividends. By focusing on the high level behavior application instead of implementation details, your tests are more resilient to changes in details that do not change high level behavior.

Unit tests tend to depend on implementation details and as a result can fair quite poorly by this metric. 



## Diagnostic value
All other things being equal, if a test fails, the faster that a programmer is able to locate the source of the failure, the more valuable the test is. If a test only tests one thing, then the source of the failure is obvious. An end to end test, while certainly important and valuable, could potentially have multiple sources of failure, but little diagnostic value. As it is still extremely relevant to our user's ability to solve problems, e2e tests can have value despite this potential shortcoming.

Generally speaking the best way to maximize the diagnostic value of tests is to test one thing per test case. You can achieve this while still focusing on high level policy and not implementation details by focusing in on individual propositions and performing any necessary intermediate validation in separate tests. Even E2E tests can often be broken up into smaller steps to help increase their diagnostic value.

## speed/automation
Your tests are useless if they never run or aren't run in a timely manner. With Reason, and especially native reason, even e2e tests can be blazingly fast. Ulrikstrid reached out to me on discord about writing some e2e tests for a web server framework he was writing. After helping him he informed me that the test ran in 3ms. Aside from language/technology choice, pushing side effects to the edges of your application and returning descriptions of actions to be taken can do a lot to promote test performance and make mocking easy. Just make sure you have tests that also run with the production dependencies.


There are a lot of great tools today for test automation, please pick and use one. It should run on every commit and every pull request. You should have some set of tests that is fast enough to run constantly while developing. Ideally you have no slow tests and can require that all tests pass in order to merge into master. If not, you should still have some set of smoke tests that must pass in order to merge or deploy code.


# Cost

## Robustness
How many of you have added a new feature and had a bunch of tests either fail with a false positive (that is fail, when they shouldn't) or fail to compile?

It slows you down tremendously if you have to constantly update a bunch of test files whenever you add new code. In my experience the best ways to avoid this are to focus on testing policy instead of details, and a proper attention to detail when it comes to software architecture and design patterns. Read the gang of 4's book, read Clean Code, read Clean Architecture. Those principles are applicable here too.

One pattern in particular that is worth calling out is the builder pattern. Here is an example

### EXAMPLE ###

## Maintainability
If a test actually does need to be updated or breaks, it is very important that the programmer who looks at it next be able to change it with confidence and rapidly understand what it does. It is vital that tests be simple to understand.

I am a fan of the AAA pattern (arrange, act, assert). 

If your arrange step is too long, you probably need some combination of builders and setup functions. Most testing frameworks offer some functions for performing setup operations before all or before each test in a test suite. Use these.

In general you should strive for cyclomatic complexity (# of code paths) of exactly 1. There are some weird edge cases with testing callbacks and things like that where you might need to make sure things fail, but that should really be it.

## Upfront investment
Writing tests can take a lot of time. Especially if your codebase is lacking in test utilities. What we just talked about in terms of robustness and maintainability can go a long way to reducing the incremental investment needed for adding each test. Identifying these high level patterns and utilities and building them is generally a sound investment.


## Thanks
Reason-native
Reason discord
Medium
Twitter
