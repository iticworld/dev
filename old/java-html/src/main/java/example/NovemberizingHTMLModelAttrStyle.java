package example;

import novemberizing.html.model.attr.Style;

public class NovemberizingHTMLModelAttrStyle {
    @SuppressWarnings("ConstantConditions")
    public static void main(String[] args) {
        functional.json.init();
        System.out.println(Style.name);
        System.out.println(functional.json.from(new Style()));
        System.out.println(functional.json.from(new Style("background", "#000000")));
        Style style = new Style();
        style.name("color");
        System.out.println(functional.json.from(style));
        style.value("color: #FFFFFF;");
        System.out.println(functional.json.from(style));
        System.out.println(style.name());
        System.out.println(style.value());
        style.put("background-color", "#050505");
        style.put("font-size", "12pt");
        System.out.println(functional.json.from(style));
        System.out.println(style.get("font-size"));
        style.del("background-color");
        System.out.println(functional.json.from(style));
        Style y = style;
        System.out.println("equals: " + style.equals(y));
        y = new Style("background", "#000000");
        System.out.println("equals: " + style.equals(y));
        y = style;
        style = new Style();
        style.put("color", "#FFFFFF");
        style.put("font-size", "12pt");
        System.out.println("equals: " + style.equals(y));
        style.clear();
        System.out.println(functional.json.from(style));
    }
}
