package example;

import hornet.editor.application.html.NovemberizingHTMLAdapter;
import hornet.editor.html.Sample;
import org.jsoup.nodes.Document;

public class ExampleTraverseDocument {
    public static void main(String[] args) {
        functional.html.init(new NovemberizingHTMLAdapter());
        Document document = functional.html.to.document(Sample.get());
        functional.html.traverse(document, (start, end, depth, n) -> {
            System.out.println("[" + n.outerHtml() + "]");
            return true;
        });
    }
}
