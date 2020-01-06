# JAVASCRIPT

## DATA STRUCTURE VISUALIZATION

__BINARY SEARCH TREE VISUALIZATION EXAMPLE__

```
<!doctype html>
<html>
<head>
    <meta charset="utf-8">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
    <title>NOVEMBERIZING - DATA STRUCTURE VISUALIZATION</title>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.7.2/Chart.js" type="text/javascript"></script>
    <script src="novemberizing.js"></script>
    <style>
        canvas {
            -moz-user-select: none;
            -webkit-user-select: none;
            -ms-user-select: none;
        }
    </style>
</head>
<body>
<div align="center">
    <table width="800" cellpadding="=0" cellspacing="0" border="0">
        <tr><td id="view"></td></tr>
    </table>
</div>
<script>
    novemberizing.chart.init();
    novemberizing.tree.show("{\"v\":[{\"x\":16,\"y\":5,\"v\":\"0\"},{\"x\":24,\"y\":4,\"v\":\"10\"},{\"x\":20,\"y\":3,\"v\":\"3\"},{\"x\":28,\"y\":3,\"v\":\"29\"},{\"x\":26,\"y\":2,\"v\":\"21\"},{\"x\":30,\"y\":2,\"v\":\"49\"},{\"x\":25,\"y\":1,\"v\":\"14\"}],\"horizontal\":32,\"vertical\":5}", "binary search tree", "view");
</script>
</body>
</html>
```

__RED BLACK TREE VISUALIZATION EXAMPLE__

```
<!doctype html>
<html>
<head>
    <meta charset="utf-8">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
    <title>NOVEMBERIZING - DATA STRUCTURE VISUALIZATION</title>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.7.2/Chart.js" type="text/javascript"></script>
    <script src="novemberizing.js"></script>
    <style>
        canvas {
            -moz-user-select: none;
            -webkit-user-select: none;
            -ms-user-select: none;
        }
    </style>
</head>
<body>
<div align="center">
    <table width="800" cellpadding="=0" cellspacing="0" border="0">
        <tr><td id="view"></td></tr>
    </table>
</div>
<script>
    novemberizing.chart.init();
    novemberizing.tree.show("{\"r\":[{\"x\":16,\"y\":5,\"v\":\"R(28)\"},{\"x\":56,\"y\":4,\"v\":\"R(88)\"},{\"x\":34,\"y\":2,\"v\":\"R(58)\"},{\"x\":3,\"y\":1,\"v\":\"R(7)\"},{\"x\":17,\"y\":1,\"v\":\"R(37)\"},{\"x\":21,\"y\":1,\"v\":\"R(41)\"},{\"x\":31,\"y\":1,\"v\":\"R(53)\"}],\"b\":[{\"x\":32,\"y\":6,\"v\":\"B(54)\"},{\"x\":48,\"y\":5,\"v\":\"B(76)\"},{\"x\":8,\"y\":4,\"v\":\"B(17)\"},{\"x\":24,\"y\":4,\"v\":\"B(45)\"},{\"x\":40,\"y\":4,\"v\":\"B(66)\"},{\"x\":4,\"y\":3,\"v\":\"B(8)\"},{\"x\":12,\"y\":3,\"v\":\"B(22)\"},{\"x\":20,\"y\":3,\"v\":\"B(40)\"},{\"x\":28,\"y\":3,\"v\":\"B(51)\"},{\"x\":36,\"y\":3,\"v\":\"B(60)\"},{\"x\":44,\"y\":3,\"v\":\"B(70)\"},{\"x\":52,\"y\":3,\"v\":\"B(84)\"},{\"x\":60,\"y\":3,\"v\":\"B(94)\"},{\"x\":2,\"y\":2,\"v\":\"B(6)\"},{\"x\":6,\"y\":2,\"v\":\"B(9)\"},{\"x\":10,\"y\":2,\"v\":\"B(19)\"},{\"x\":14,\"y\":2,\"v\":\"B(23)\"},{\"x\":18,\"y\":2,\"v\":\"B(38)\"},{\"x\":22,\"y\":2,\"v\":\"B(43)\"},{\"x\":26,\"y\":2,\"v\":\"B(49)\"},{\"x\":30,\"y\":2,\"v\":\"B(52)\"},{\"x\":50,\"y\":2,\"v\":\"B(83)\"},{\"x\":54,\"y\":2,\"v\":\"B(86)\"},{\"x\":58,\"y\":2,\"v\":\"B(91)\"},{\"x\":62,\"y\":2,\"v\":\"B(98)\"}],\"horizontal\":64,\"vertical\":6}", "red black tree", "view");
</script>
</body>
</html>
```

## HOW TO USE

### BINARY SEARCH TREE

```
novemberizing.chart.init(); /** initialize chart property. */
novemberizing.tree.show(json, type, html parent element, vertical, horizontal);
```

__JSON__

_DATA WITH HORIZONTAL & VERTICAL_

```
{
    v: [
        { x: integer, y: integer, v: v },
        ...
    ],
    horizontal: integer,
    vertical: integer
}
```

_ONLY DATA_

```
[
    { x: integer, y: integer, v: v },
    ...
]
```

### RED BLACK TREE

```
novemberizing.chart.init(); /** initialize chart property. */
novemberizing.tree.show(json, type, html parent element, vertical, horizontal);
```

__JSON__

_DATA WITH HORIZONTAL & VERTICAL_

```
{
    r: [
        { x: integer, y: integer, v: v },
        ...
    ],
    b: [
        { x: integer, y: integer, v: v },
        ...
    ]
    horizontal: integer,
    vertical: integer
}
```

_ONLY DATA_

> INDEX ZERO IS RED, INDEX ONE IS BLACK

```
[
    [
        { x: integer, y: integer, v: v },
        ...
    ],
    [
        { x: integer, y: integer, v: v },
        ...
    ]
]
```