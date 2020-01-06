/**
 *
 * @author novemberizing <novemberizing@gmail.com>
 * @since 0.0.1
 */

import client from './git/client';
import base64 from './util/base64';
import packet from './git/packet';
import repository from './git/repository';

let __headers = new Map();

__headers.set('User-Agent', 'git/2.17.1');
__headers.set('Accept', '*/*');
// __headers.set('Accept-Encoding', 'deflate, gzip');   // todo: Refused to set unsafe header "Accept-Encoding"
__headers.set('Pragma', 'no-cache');

/**
 * git-upload-pack > git fetch pack
 *
 *
 *
 * @param url {String} url
 * @param user {String} user
 * @param password {String} password
 */
function uploadPack(url, user, password) {
    let headers = new Map(__headers);
    if(user && password){
        headers.set('Authorization', 'Basic ' + base64.encode(user + ':' + password));
    }
    client.get(url + '/info/refs?service=git-upload-pack', headers, function(event, request){
        if(request.readyState === 4) {
            if(request.status === 200) {
                // todo: support asynchronously serializing
                let lines = packet.parse(request.responseText);
                lines.forEach(function(value, index, list){
                    if(value.type === 'line') {
                        console.log(value);
                    }
                });
                // todo: implement serialize ...
                // console.log(request.responseText);
            } else {
                console.log(request.responseText);
            }
        }
    });
}

function clone(url, user, password) {
    let headers = new Map(__headers);
    if(user && password){
        headers.set('Authorization', 'Basic ' + base64.encode(user + ':' + password));
    }
    client.get(url + '/info/refs?service=git-upload-pack', headers, function(event, request){
        if(request.readyState === 4) {
            if(request.status === 200) {
                packet.parse(request.responseText);
                // todo: implement serialize ...
                console.log(request.responseText);
            } else {
                console.log(request.responseText);
            }
        }
    });
}

let git = {
    repository: repository,
    line: 'line',
    clone: clone,
    upload: {
        pack: uploadPack
    }
};

export default git;
