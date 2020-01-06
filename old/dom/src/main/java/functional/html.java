package functional;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;

import java.util.List;

public class html {
    public static Document load(String html) {
        return Jsoup.parse(functional.string.v(html));
    }

    public static List<Element> children(Element parent) { return parent != null ? parent.children() : null; }
}
