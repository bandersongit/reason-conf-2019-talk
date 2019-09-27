# reason-conf-examples


[![CircleCI](https://circleci.com/gh/yourgithubhandle/reason-conf-examples/tree/master.svg?style=svg)](https://circleci.com/gh/yourgithubhandle/reason-conf-examples/tree/master)


**Contains the following libraries and executables:**

```
reason-conf-examples@0.0.0
│
├─test/
│   name:    TestReasonConfExamples.exe
│   require: reason-conf-examples/library
│
├─library/
│   library name: reason-conf-examples/library
│   require:
│
└─executable/
    name:    ReasonConfExamplesApp.exe
    require: reason-conf-examples/library
```

## Developing:

```
npm install -g esy
git clone <this-repo>
esy install
esy build
```

## Running Binary:

After building the project, you can run the main binary that is produced.

```
esy x ReasonConfExamplesApp.exe 
```

## Running Tests:

```
# Runs the "test" command in `package.json`.
esy test
```
