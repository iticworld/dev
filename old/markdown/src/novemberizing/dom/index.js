/**
 *
 * @author novemberizing <novemberizing@gmail.com>
 * @since 0.0.1
 */

import {NovemberizingDomException} from './exception'
import functional from "novemberizing";
import {Article, Document} from "./node";

export default class NovemberizingDom {
  static from(type, data){
    switch(type){
      case 'markdown': return NovemberizingDom._markdown(data);
      default: throw new NovemberizingDomException(`${type} is not support`);
    }
  }

  static _markdown(data, config) {
    config = config || JSON.parse(functional.fs.get('./config.json'));
    const document = new Document(config);
    const lines = data.split(/\r?\n/g);
    // article serialize
    if(!lines[0].startsWith('# ')){
      throw new NovemberizingDomException('!lines[0].startsWith(\'# \')');
    }
    let start = lines[0].indexOf('[', 2);
    let end = start >= 0 ? lines[0].indexOf(']', start) : -1;
    // generate article category
    const category = lines[0].substring(start + 1, end);
    // generate article title
    const title = end > 0 ? lines[0].substring(end + 1) : lines[0].substring(2);
    let index = 1;
    let summary = '';
    for(index = 1;index < lines.length;index++) {
      if(lines[index].startsWith('> ')) {
        for(;index < lines.length && lines[index].startsWith('>');index++) {
          const line = functional.string.trim(lines[index].substring(1));
          if(line.length > 0) {
            summary += `${line} `;
          } else {
            summary = summary.trim();
            summary += '<br />';
          }
        }
        break;
      }
    }
    // generate article date
    let date = '';
    for(index = index + 1;index < lines.length;index++) {
      const line = lines[index].trim();
      if(lines[index].match(/^\d{4}\/(0[1-9]|1[012])\/(0[1-9]|[12][0-9]|3[0-1])$/)){
        const strings = line.split('/');
        date = new Date(Date.UTC(strings[0], strings[1] - 1, strings[2]));
        break;
      }
    }
    // split header & content
    for(index = index + 1;index < lines.length;index++) {
      const line = lines[index].trim();
      if(line === '----') {
        for(index = index + 1; index < lines.length && line.length === 0; index++) {}
        break;
      }
    }
    let content = '';
    for(;index < lines.length;index++) {
      const line = lines[index];
      if(functional.string.trim(line) !== ''){
        content += `${line}\n`;
      } else {
        content = content.trim();
        content += '<br />\n';
      }
    }
    const article = new Article(category, title, summary, date, content);
    document.push(article);
    console.log(document);
    return document.html(functional.fs.get('./index.ejs'));
  }
}
