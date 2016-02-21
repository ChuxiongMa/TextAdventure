# Textadventure

## Getting started

```shell
git clone git@csil-git1.cs.surrey.sfu.ca:373-15-3-gelato/textadventure.git
mkdir build
cd build
cmake -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ ../textadventure
make
```

### Using Atom

If you're using Atom, you can save yourself from having to tap "Alt/Cmd + Tab" by installing the [atom-build](https://atom.io/packages/build) plugin, and then including the following config in a `.atom-build.json` file at the root of the project:

```
{
  "cmd": "/usr/bin/make",
  "args": ["-C", "../build"],
  "name": "build",
  "sh": false
}
```

## Testing

```shell
make check
```
