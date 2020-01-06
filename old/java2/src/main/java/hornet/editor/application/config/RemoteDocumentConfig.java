package hornet.editor.application.config;

import hornet.editor.application.endpoint.RemoteDocumentEndpoint;
import org.springframework.boot.autoconfigure.EnableAutoConfiguration;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.socket.config.annotation.EnableWebSocket;
import org.springframework.web.socket.server.standard.ServerEndpointExporter;

@Configuration
@EnableWebSocket
@EnableAutoConfiguration
public class RemoteDocumentConfig {
    @Bean
    public ServerEndpointExporter serverEndpointExporter() {
        return new ServerEndpointExporter();
    }

    @Bean
    public RemoteDocumentEndpoint remoteDocumentEndpoint() {
        return new RemoteDocumentEndpoint();
    }
}
