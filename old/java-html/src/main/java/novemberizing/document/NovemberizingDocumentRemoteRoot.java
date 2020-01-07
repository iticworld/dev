package novemberizing.document;

import novemberizing.html.server.DocumentRemoteRoot;
import org.jsoup.nodes.Element;

import java.util.List;
import java.util.UUID;

public class NovemberizingDocumentRemoteRoot extends DocumentRemoteRoot {

    @Override
    public void load() {
        lock();
        if(__document == null) {
            __document = functional.html.to.document("<h2>Document No.${id}</h2>\n" +
                    "  <p>\n" +
                    "    <span style=\"text-decoration: line-through;\"><span style=\"text-decoration: underline;\">hello, </span></span>Collabee\n" +
                    "  </p>\n" +
                    "  <p>허 생원은 오늘 밤도 또 그 이야기를 끄집어내려는 것이다. 조 선달은 친구가 된 이래 귀에 못이 박히도록 들어왔다. 그렇다고 싫증은 낼 수도 없었으나 허 생원은 시치미를 떼고 되풀이할 대로는 되풀이하고야 말았다.</p>\n" +
                    "  <blockquote><p>달밤에는 그런 이야기가 격에 맞거든.</p></blockquote>\n" +
                    "  <p>조 선달 편을 바라는 보았으나 물론 미안해서가 아니라 달빛에 감동하여서였다.</p>\n" +
                    "  <p>이지러는 졌으나 보름을 갓 지난 달은 부드러운 빛을 흔붓이 흘리고 있다. 대화까지는 팔십 리의 밤길, 고개를 둘이나 넘고 개울을 하나 건너고 벌판과 산길을 걸어야 된다. 길은 지금 긴 산허리에 걸려 있다.</p>\n" +
                    "  <p>길은 지금 긴 산허리에 걸려 있다. 밤중을 지난 무렵인지 죽은 듯이 고요한 속에서 짐승 같은 달의 숨소리가 손에 잡힐 듯이 들리며, 콩 포기와 옥수수 잎새가 한층 달에 푸르게 젖었다. 산허리는 온통 메밀밭이어서 피기 시작한 꽃이 소금을 뿌린 듯이 흐붓한 달빛에 숨이 막힐 지경이다.</p>\n" +
                    "\n" +
                    "  <h2>코드 예제</h2>\n" +
                    "  <p>마크다운 #규칙 사용 옵션(useMarkdownRule)이 켜져있는 경우 간단하게 백틱 세번(\\`) 입력하여 코드 모드로 전환할 수 있습니다.</p>\n" +
                    "  <pre class=\"lang-javascript\" data-lang=\"javascript\"><code>// from main.js\n" +
                    "var editor = new CollabeeHornetEditor({\n" +
                    "  containerNode: document.querySelector('#editor'),\n" +
                    "  contentNode: document.querySelector('#content'),\n" +
                    "  className: 'collabee-editor',\n" +
                    "  code_block: {\n" +
                    "    codemirror: {\n" +
                    "      modeURL: 'https://cdnjs.cloudflare.com/ajax/libs/codemirror/5.38.0/mode/%N/%N.min.js',\n" +
                    "    },\n" +
                    "  },\n" +
                    "  placeholder: {\n" +
                    "    message: '텍스트를 입력하세요',\n" +
                    "  },\n" +
                    "  menubar: {\n" +
                    "    items: 'clear | strong em underline del | ol ul code_block blockquote',\n" +
                    "  },\n" +
                    "});</code></pre>\n" +
                    "<p>Lorem <span style=\"text-decoration: underline;\"><span style=\"color: red;\">ipsum</span></span> dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.</p>\n" +
                    "<p>${faker.lorem.sentence()} ${faker.random.uuid()}</p>");
            __version = 0L;
        }
        unlock();
    }

    public NovemberizingDocumentRemoteRoot(String id) {
        super(id);
    }
}
