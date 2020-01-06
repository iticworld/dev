package hornet.editor.application;

import hornet.editor.application.html.NovemberizingHTMLAdapter;
import hornet.editor.application.html.NovemberizingRemoteDocument;
import hornet.editor.html.server.RemoteDocument;
import hornet.editor.html.server.json.RemoteDocumentJsonSerializer;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.scheduling.annotation.EnableScheduling;

@SpringBootApplication
@EnableScheduling
public class Application {

    public static void main(String[] args) {
        functional.json.init(o -> {
            o.registerTypeAdapter(RemoteDocument.class, new RemoteDocumentJsonSerializer());
            o.registerTypeAdapter(NovemberizingRemoteDocument.class, new RemoteDocumentJsonSerializer());
        });
        functional.html.init(new NovemberizingHTMLAdapter());
        SpringApplication.run(Application.class, args);
    }
}
