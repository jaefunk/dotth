

var request = require('sync-request');
var cheerio = require('cheerio');
var voca = require('voca');
var fs = require('fs');
var target_url = 'http://animalhospital.moacha.com/?search_name=&location=&page=';
var last_result = '';
// 563
for (var page = 1; page < 564; ++page) {
  console.log("page now: ", page);
  var last_url = target_url + page;
  var res = request('GET', last_url);
  const $ = cheerio.load(res.getBody());
  for (var i = 0; i < 30; ++i) {
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
      tmp = voca.replaceAll(strings[index], '-', '');
      if (line == 2 && index == 1 && voca.isNumeric(tmp))
        last_result += "\"" + "\"" + ','
      last_result += "\"" + strings[index] + "\"" + ','
    }
    last_result += '\n';
  }

  if (page % 100 == 0 || page == 563)
  {
    var filename = 'text' + page + '.csv';
    fs.writeFileSync(filename, last_result, 'utf8');
    last_result = '';
  }
}


//console.log(last_result);
