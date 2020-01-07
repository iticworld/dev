/**
 *
 * @author novemberizing <novemberizing@gmail.com>
 * @since 0.0.1
 */

import ejs from "ejs";
import functional from "novemberizing";

export class Node {
  constructor(type){
    this._type = type;
    this._children = [];
    this._attributes = {};
  }

  json() {
    return {
      type: this._type
    }
  }
}

Node.TextNodeType = 'text';
Node.DocumentNodeType = 'document';
Node.ElementNodeType = 'element';
Node.HeadLineType = 'headline';
Node.ArticleNodeType = 'article';

export class Article extends Node {
  constructor(category, title, summary, date, content) {
    super(Node.ArticleNodeType);
    category = functional.string.trim(category);
    title = functional.string.trim(title);
    summary = functional.string.trim(summary);
    this._content = content;
    this._attributes = {category, title, summary, date, ...this._attributes};
  }

  get subject() {
    return this._attributes.title;
  }

  get summary(){
    return this._attributes.summary;
  }

  get content() {
    return this._content;
  }
}

export class Document extends Node{
  constructor(config){
    super(Node.DocumentNodeType);
    this._attributes = {
      site:{
        name: config.site.name,
        description: config.site.description,
        summary: config.site.summary,
        url: config.site.url
      },
      ...this._attributes
    };
  }

  get name() {
    return this._attributes.site.name;
  }

  get description(){
    return this._attributes.site.description;
  }

  get summary(){
    return this._attributes.site.summary;
  }

  get homepage(){
    return this._attributes.site.url;
  }

  get articles(){
    return this._children;
  }

  get footer(){
    return `<a href="${this._attributes.site.url}">novemberizing</a>, powered by <a href="https://gitlab.com/novemberizing/javascript/markdown">novemberizing's markdown 0.0.1</a>`;
  }

  push(article){
    this._children.push(article);
  }

  html(template) {
    return ejs.render(template, {
      site: {
        name: this.name,
        description: this.description,
        summary: this.summary,
        url: this.homepage
      },
      articles: this.articles,
      footer: this.footer
    });
  }
}
