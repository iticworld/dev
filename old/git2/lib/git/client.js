/**
 *
 * @author novemberizing <novemberizing@gmail.com>
 * @since 0.0.1
 */

import { base64 } from '../util/base64';
import { XMLHttpRequest } from 'xmlhttprequest';
import { packet } from './packet';

export class client {
    static req(url, user, password) {
        let request = new XMLHttpRequest();
        request.open('GET', url + '/info/refs?service=git-upload-pack', true);
        request.setRequestHeader('Authorization', 'Basic ' + base64.encode(user + ':' + password));
        request.setRequestHeader('User-Agent', 'git/2.17.1');
        request.setRequestHeader('Accept', '*/*');
        // todo: Refused to set unsafe header "Accept-Encoding"
        request.setRequestHeader('Accept-Encoding', 'gzip');
        request.setRequestHeader('Accept-Language', 'en-US, *;q=0.9');
        request.setRequestHeader('Pragma', 'no-cache');
        request.onreadystatechange = function(event){
            if(request.readyState === 4) {
                if(request.status === 200) {
                    let lines = packet.parse(request.responseText);
                    console.log(lines);
                    // git.parse(request.responseText);
                    // self.parse(request.responseText);
                } else {
                    console.error(request.responseText);
                }
            }
        };
        request.send(null);
    }
}

// export class git {
//
//
//
//
//
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