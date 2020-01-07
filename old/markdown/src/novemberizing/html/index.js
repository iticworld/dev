/**
 *
 * @author novemberizing <novemberizing@gmail.com>
 * @since 0.0.1
 */

import functional from 'novemberizing';
import path from 'path';

import NovemberizingDom from '../dom';
import {NovemberizingHtmlException} from "./exception";

export default class NovemberizingHtml {
  static exec(parameters){
    switch(parameters[0]){
      case 'generate': functional.fs.set(parameters[2],NovemberizingHtml.from(parameters[1])); break;
    }
  }
  static from(location){
    const data = functional.fs.get(location);
    const extension = path.extname(location);
    switch(extension){
      case '.md': return NovemberizingDom.from('markdown', data);
      default: throw new NovemberizingHtmlException(`${extension} is not support`);
    }
  }

  //
  // static exec(type, source, destination) {
  //   switch(type){
  //     case 'generate': NovemberizingHtml.generate(source, destination); break;
  //     default: throw new NovemberizingException(`${type} not support`);
  //   }
  // }
  // static generate(source, destination) {
  //   const location = source;
  //   const extension = path.extname(location);
  //   switch(extension) {
  //     case '.md': functional.fs.set(destination, NovemberizingHtml.fromMarkdown(functional.fs.get(location))); break;
  //     default: throw new NovemberizingException(`${extension} not support`);
  //   }
  // }
  // static fromMarkdown(data) {
  //   const doc = NovemberizingDoc.fromMarkdown(data);
  //   return ejs.render(functional.fs.get('./index.ejs'), {site:doc.site.json,articles:doc.articles,footer:'footer'});
  // }
}