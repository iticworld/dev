package novemberizing.ws;

import novemberizing.document.NovemberizingHTMLAdjustor;
import novemberizing.html.server.DocumentRemoteRoot;
import novemberizing.html.server.json.GsonDocumentRemoteRootSerializer;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;

public class Example {
    public static void main(String[] args) {
        // node: <p id="690a580a-a60d-46ef-8fc0-41c06789336c">조 선달 편을 바라는 보았으나 물론 미안해서가 아니라 달빛에 감동하여서였다.</p>
        // from: 42
        // to: 44
        // id: 690a580a-a60d-46ef-8fc0-41c06789336c
        // from: 42
        // to: 44
        functional.json.init(o -> {
            o.registerTypeAdapter(DocumentRemoteRoot.class, new GsonDocumentRemoteRootSerializer());
        });
        functional.html.init(new NovemberizingHTMLAdjustor());

        Document document = functional.html.to.document("<p id=\"690a580a-a60d-46ef-8fc0-41c06789336c\">조 선달 편을 바라는 보았으나 물론 미안해서가 아니라 달빛에 감동하여서였다.</p>");
        Element element = document.getElementById("690a580a-a60d-46ef-8fc0-41c06789336c");
        System.out.println("length: " + functional.html.length(element));
    }
}
