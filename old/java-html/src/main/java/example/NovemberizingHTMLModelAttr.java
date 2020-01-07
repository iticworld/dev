package example;

import novemberizing.html.model.Attr;

public class NovemberizingHTMLModelAttr {
    public static void main(String[] args) {
        functional.json.init();
        System.out.println(functional.json.from(new Attr()));
        System.out.println(functional.json.from(new Attr("id")));
        System.out.println(functional.json.from(new Attr("id","hello")));
        Attr attr = new Attr();
        attr.name("class");
        System.out.println(functional.json.from(attr));
        attr.value("world");
        System.out.println(functional.json.from(attr));
        System.out.println(attr.name());
        System.out.println(attr.value());
    }
}
