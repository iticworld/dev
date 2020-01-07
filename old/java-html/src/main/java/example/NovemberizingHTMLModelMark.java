package example;

import novemberizing.html.model.Attr;
import novemberizing.html.model.Mark;
import novemberizing.html.model.attr.Style;

public class NovemberizingHTMLModelMark {
    public static void main(String[] args) {
        functional.json.init();
        Mark mark = new Mark();
        System.out.println(functional.json.from(mark));
        mark = new Mark("p");
        System.out.println(functional.json.from(mark));
        mark = new Mark("span", new Style("background-color", "#00ff00"));
        System.out.println(functional.json.from(mark));
        mark = new Mark("div", functional.list.gen(new Style("color", "#ffffff"), new Attr("id", "hello")));
        System.out.println(functional.json.from(mark));
        System.out.println(mark.tag());
        System.out.println(functional.json.from(mark.attrs()));

        mark = new Mark(new Attr("class", "world"));
        System.out.println(functional.json.from(mark));
        mark.put(new Attr("total", "0"));
        System.out.println(functional.json.from(mark));
        mark.del("class");
        System.out.println(functional.json.from(mark));
        System.out.println(functional.json.from(mark.get("total")));
        mark.clear();
        System.out.println(functional.json.from(mark));
        mark.attrs(functional.list.gen(new Style("color", "#ffffff"), new Attr("id", "hello")));
        System.out.println(functional.json.from(mark));
        mark.tag("span");
        System.out.println(functional.json.from(mark));
    }
}
