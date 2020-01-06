# RED BLACK TREE

__EMSCRIPTEN BUILD__

```
emcc main.c node.c tree.c util.c -o red.black.tree.js -s "EXTRA_EXPORTED_RUNTIME_METHODS=['Pointer_stringify']"
```