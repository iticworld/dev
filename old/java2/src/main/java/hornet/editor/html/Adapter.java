package hornet.editor.html;

import novemberizing.tuple.Triple;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;

public interface Adapter {
    Document adjust(Document document);
    String adjust(String html);
    Triple<Element, Integer, Integer> adjust(Element element, int index);
    int length(String name);
    int index(Element element, int index);
    String name(String v);
}
