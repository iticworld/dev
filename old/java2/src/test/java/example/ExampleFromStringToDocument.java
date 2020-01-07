package example;

import hornet.editor.application.html.NovemberizingHTMLAdapter;
import hornet.editor.html.Sample;

public class ExampleFromStringToDocument {
    public static void main(String[] args) {
        functional.html.init(new NovemberizingHTMLAdapter());
        // System.out.println(functional.html.adjust.html(Sample.get()));
        System.out.println(functional.html.to.document(Sample.get()));
    }
}
