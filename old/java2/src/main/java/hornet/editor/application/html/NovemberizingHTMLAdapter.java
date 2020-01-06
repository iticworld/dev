package hornet.editor.application.html;

import hornet.editor.html.Adapter;
import novemberizing.tuple.Triple;
import org.jsoup.helper.StringUtil;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.nodes.TextNode;

import java.util.LinkedList;
import java.util.List;
import java.util.UUID;

public class NovemberizingHTMLAdapter implements Adapter {
    @Override
    public Document adjust(Document document) {
        Document.OutputSettings settings = document.outputSettings();
        settings.indentAmount(0);
        settings.prettyPrint(false);
        document.outputSettings(settings);
        List<Element> elements = document.select("*");
        LinkedList<TextNode> nodes = new LinkedList<>();
        for(Element element : elements) {
            if(!functional.html.is.code(element)) {
                for(TextNode node : element.textNodes()) {
                    String s = node.getWholeText();
                    s = StringUtil.normaliseWhitespace(s);
                    // System.err.println("태곤님한테 WHITE 스페이스에 대한 이야기를 듣고 올바르게 구현하자.");
                    if(s.length() == 0) {
                        nodes.add(node);
                    } else if(s.length() == 1 && StringUtil.isWhitespace(s.charAt(0))) {
                        nodes.add(node);
                    } else {
                        s = s.replace(" ", "_");
                        // s = s.trim();
                        node.text(s);
                    }
                }
            }
        }
        for(TextNode node : nodes) {
            node.remove();
        }
        generate(document.select("p"));
        generate(document.select("pre"));
        generate(document.select("h1"));
        generate(document.select("h2"));
        generate(document.select("h3"));
        generate(document.select("h4"));
        generate(document.select("h5"));
        generate(document.select("h6"));
        generate(document.select("blockquote"));
        generate(document.select("ol"));
        generate(document.select("ul"));
        return document;
    }

    public void generate(List<Element> elements) {
        if(functional.list.exist(elements)) {
            for(Element element : elements) {
                if(functional.string.empty(element.attr("id"))) {
                    element.attr("id", functional.string.v(UUID.randomUUID()));
                }
            }
        }
    }

    @Override
    public String adjust(String html) {
        String s = functional.string.v(html);
        s = s.replaceAll(">\\s+", ">");
        s = s.replaceAll("\\s+<", "<");
        return s;
    }

    @Override
    public Triple<Element, Integer, Integer> adjust(Element element, int index) {
        if(element != null) {
            if(functional.string.contain(element.nodeName(), "p", "h1", "h2", "h3", "h4", "h5", "h6")) {
                return new Triple<>(element, 0, functional.html.length(element));
            } else if(functional.string.equal(element.nodeName(), "blockquote")) {
                List<Element> elements = element.children();
                int total = 0;
                for(Element node : elements) {
                    int length = functional.html.length(node);
                    if(total <= index && index < total + length) {
                        return new Triple<>(node, total, total + length);
                    }
                    total += length;
                }
                throw new RuntimeException("");
            } else {
                throw new RuntimeException("");
            }
        }
        return new Triple<>(null, 0, 0);

    }

    @Override
    public int length(String name) {
        return functional.string.contain(name, "blockquote", "pre", "p", "h1", "h2", "h3", "h4", "h5", "h6", "ol", "ul") ? 2 : 0;
    }

    @Override
    public int index(Element element, int index) {
        return element != null && functional.string.contain(element.nodeName(), "blockquote") ? index - 1 : index;
    }

    @Override
    public String name(String v) {
        return functional.string.empty(v) ? "span" : v;
    }
}
