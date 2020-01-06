package novemberizing.ws;

import novemberizing.document.NovemberizingHTMLAdjustor;
import novemberizing.html.server.DocumentRemoteRoot;
import novemberizing.html.server.json.GsonDocumentRemoteRootSerializer;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.scheduling.annotation.EnableScheduling;

@SpringBootApplication
@EnableScheduling
public class Application {


    public static void main(String[] args) {
        functional.json.init(o -> {
            o.registerTypeAdapter(DocumentRemoteRoot.class, new GsonDocumentRemoteRootSerializer());
        });
        functional.html.init(new NovemberizingHTMLAdjustor());

        SpringApplication.run(Application.class, args);
    }
}
