/**
 *
 * @author novemberizing <novemberizing@gmail.com>
 * @since 0.0.1
 */

import headers from './headers';
import client from './client';
import packet from "./packet";
import pack from "./pack";
import parameter from "./parameter";
import pair from "./pair";
import flush from "./lines/flush";
import line from "./line";

/**
 * retrieve all pack information command.
 *
 * @param url {String} url
 * @param authorization {pair} authorization pair
 * @returns {Promise} promise
 */
function retrievePack(url, authorization) {
    return new Promise((resolve, reject) => {
        client.get(url + '/info/refs?service=git-upload-pack', client.header(headers, authorization, new pair('Pragma', 'no-cache')), (request, exception) => {
            if(exception) {
                reject(exception);
            } else {
                try {
                    let lines = packet.parse(request.responseText);
                    if(lines.length > 0) {
                        if(lines[0].type === 'service' && lines[0].name === 'git-upload-pack') {
                            let packs = new Map();
                            for(let i = 1; i < lines.length; i++) {
                                if(lines[i].type === 'flush') {
                                    // todo: how to implement flush packet.
                                    continue;
                                }
                                if(lines[i].type === 'line') {
                                    if(lines[i].data.indexOf('\0') !== -1) {
                                        let space = lines[i].data.indexOf(' ');
                                        let nil = lines[i].data.indexOf('\0', space + 1);
                                        let parameters = [];
                                        let strings = lines[i].data.slice(nil + 1, -1).split(' ');
                                        strings.forEach((value, index, list) => {
                                            void(index);
                                            void(list);
                                            let o = value.split('=');
                                            parameters.push(new parameter(o[0], o.length > 1 ? o[1] :  undefined));
                                        });
                                        let id = lines[i].data.slice(0, space);
                                        if(!packs.has(id)) {
                                            packs.set(id, new pack(id,
                                                               lines[i].data.slice(space + 1, nil),
                                                               parameters));
                                        } else {
                                            // todo implement this
                                        }

                                    } else {
                                        let space = lines[i].data.indexOf(' ');
                                        let id = lines[i].data.slice(0, space);
                                        if(!packs.has(id)) {
                                            packs.set(id, new pack(lines[i].data.slice(0, space), lines[i].data.slice(space + 1, -1)));
                                        } else {
                                            // todo implement this
                                        }
                                    }
                                }
                            }
                            resolve(packs);
                        } else {
                            reject({request: request, exception: new Error('lines[0].type === \'service\' && lines.[0].name === \'git-upload-pack\'')});
                        }
                    } else {
                        reject({request: request, exception: new Error('lines.length === 0')});
                    }
                } catch(e) {
                    reject(e);
                }
            }
        });
    });
}

/**
 *
 00a2want c3599bbc143b3511f678c37d771123fc2feb712c multi_ack_detailed no-done side-band-64k thin-pack ofs-delta deepen-since deepen-not agent=git/2.19.0.windows.1
 00000009done

 *
 * @param url
 * @param authorization
 * @param packs
 * @returns {Promise}
 */
function wantPack(url, authorization, packs) {
    // let options = ['multi_ack_detailed', 'no-done', 'side-band-64k', 'thin-pack', 'ofs-delta', 'deepen-since', 'deepen-not', 'agent=git/2.17.1'];
    let body = '';
    packs.forEach((value, key, map) => {
        void(map);
        body += value.want();
    });
    body += flush.gen();
    body += line.gen('done\n');
    console.log(body);
    return new Promise((resolve, reject) => {
        // Accept: application/x-git-upload-pack-result
        client.post(url + '/git-upload-pack', client.header(headers, authorization, new pair('Content-Type', 'application/x-git-upload-pack-request'), new pair('Accept', 'application/x-git-upload-pack-result')), body, (request, exception) => {
            if(exception){
                console.error(request);
                console.error(exception);
                reject(exception);
            } else {
                /**
                 * todo: implement serialize
                 */
                console.log(request.responseText);
                resolve(request.responseText);
            }
        });
        /**
         *
         *
         *
         */
    });
}

let command = {
    upload: {
        pack: {
            info: retrievePack,
            want: wantPack
        }
    }
};

export default command;
