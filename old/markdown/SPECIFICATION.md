# SPECIFICATION

```
# [CATEGORY] TITLE

> [summary]
```



1. 헤드라인은 '#' 으로 시작하며 생성될 파일 패스를 담고 있어야 한다.

```
# TITLE
```

# TITLE


devDependencies§

If someone is planning on downloading and using your module in their program, then they probably don’t want or need to download and build the external test or documentation framework that you use.

In this case, it’s best to map these additional items in a devDependencies object.

These things will be installed when doing npm link or npm install from the root of a package, and can be managed like any other npm configuration param. See npm-config for more on the topic.

For build steps that are not platform-specific, such as compiling CoffeeScript or other languages to JavaScript, use the prepare script to do this, and make the required package a devDependency.

For example:

{ "name": "ethopia-waza",
  "description": "a delightfully fruity coffee varietal",
  "version": "1.2.3",
  "devDependencies": {
    "coffee-script": "~1.6.3"
  },
  "scripts": {
    "prepare": "coffee -o lib/ -c src/waza.coffee"
  },
  "main": "lib/waza.js"
}

The prepare script will be run before publishing, so that users can consume the functionality without requiring them to compile it themselves. In dev mode (ie, locally running npm install), it’ll run this script as well, so that you can test it easily.
