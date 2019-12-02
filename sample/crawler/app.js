

var request = require('request');
var cheerio = require('cheerio');
var voca = require('voca');

var target_url = 'http://animalhospital.moacha.com/?search_name=&location=&page=';
// 563
for (var page = 1; page < 3; ++page) {
  request.get({ url: target_url + page }, function (err, res, body) {
    const $ = cheerio.load(body);

    for (var i = 0; i < 30; ++i) {

      console.log('////////////////////////////////////', i);
      var aaa = 'div#index_container ul#list_accordion div#item_heading' + i;
      const aa = $(aaa).text();
      let title = aa;
      title = voca.replaceAll(title, '\t', '');
      title = voca.replaceAll(title, '\r\n', '');
      title = voca.replaceAll(title, '\n', '!@#!@#');
      title = voca.replaceAll(title, '!@#!@#', '!@#');
      title = voca.replaceAll(title, '!@#!@#', '!@#');
      title = voca.replaceAll(title, '!@#!@#', '!@#');
      title = voca.replaceAll(title, '!@#!@#', '!@#');
      title = voca.replaceAll(title, '!@#!@#', '!@#');
      title = voca.replaceAll(title, '!@#!@#', '!@#');
      title = voca.replaceAll(title, '!@#', '\n');
      title = voca.trim(title);
      var pick = voca.indexOf(title, "인허가일", 0);
      title = voca.substring(title, 0, pick);

      var line = voca.countWhere(title, function (character, index, str) {
        return character === '\n';
      });
      var strings = voca.split(title, '\n');

      for (var index = 0; index < line; ++index) {
        console.log(strings[index]);
      }
    }
  });
}
