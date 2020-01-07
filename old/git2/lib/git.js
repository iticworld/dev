/**
 *
 * @author novemberizing <novemberizing@gmail.com>
 * @since 0.0.1
 */

import { client } from './git/client';

/**
 *
 *
 */
export class git {
    static clone(url, user, password){
        client.req(url, user, password);
    }
    /**
     * git.clone('http://git.example.com',
     */
}

// /**
//  *
//  * @author novemberizing <novemberizing@gmail.com>
//  * @since 0.0.1
//  * @see https://developer.mozilla.org/ko/docs/XMLHttpRequest
//  * @see https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Authorization
//  * @see https://developer.mozilla.org/en-US/docs/Web/API/WindowBase64/Base64_encoding_and_decoding
//  */
//
// import { XMLHttpRequest } from 'xmlhttprequest';
// import { TextEncoder } from 'text-encoding';
// import base64js from 'base64-js';
//
// // todo: refactor base64 util class
// function Base64Encode(str, encoding = 'utf-8') {
//     var bytes = new (TextEncoder || TextEncoderLite)(encoding).encode(str);
//     return base64js.fromByteArray(bytes);
// }
//
// function Base64Decode(str, encoding = 'utf-8') {
//     var bytes = base64js.toByteArray(str);
//     return new (TextDecoder || TextDecoderLite)(encoding).decode(bytes);
// }
//
// export class packet {
//     constructor(length, data){
//         this.length = length;
//         if(this.length !== 0){
//             this.data = data;
//         } else {
//             this.data = undefined;
//         }
//     }
// }
//
// /**
//  *
//  *
//  */
// export class git {
//     constructor(url, user, password){
//         this.url = url;
//         this.user = user;
//         this.password = password;
//         this.authorization = Base64Encode(this.user + ':' + this.password);
//     }
//
//     static parse(s){
//         let start = 0;
//         let length = 0;
//         let lines = [];
//
//         while(start < s.length) {
//             length = parseInt('0x' + s.slice(start, start + 4));
//             if(length !== 0) {
//                 lines.push(new packet(length, s.slice(start + 4, start + length)));
//                 start += length;
//             } else {
//                 lines.push(new packet(length));
//                 start += 4;
//             }
//         }
//         return lines;
//     }
//
//     clone(){
//         console.log(this);
//         let request = new XMLHttpRequest();
//         request.open('GET', this.url + '/info/refs?service=git-upload-pack', true);
//         request.setRequestHeader('Authorization', 'Basic ' + this.authorization);
//         request.setRequestHeader('User-Agent', 'git/2.17.1');
//         request.setRequestHeader('Accept', '*/*');
//         // todo: Refused to set unsafe header "Accept-Encoding"
//         request.setRequestHeader('Accept-Encoding', 'gzip');
//         request.setRequestHeader('Accept-Language', 'en-US, *;q=0.9');
//         request.setRequestHeader('Pragma', 'no-cache');
//         let self = this;
//         request.onreadystatechange = function(event){
//             if(request.readyState === 4) {
//                 if(request.status === 200) {
//                     console.log(request.responseText);
//                     git.parse(request.responseText);
//                     // self.parse(request.responseText);
//                 } else {
//                     console.error(request.responseText);
//                 }
//             }
//         };
//         request.send(null);
//     }
// }

