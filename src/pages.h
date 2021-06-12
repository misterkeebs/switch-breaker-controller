#include <Arduino.h>

const char index_html[] PROGMEM = R"(
<!doctype html>
<html lang=en>
<head>
  <meta charset=utf-8>
  <title>MrBreaker</title>
</head>
<body>
  <div id="content">
  </div>
  <script>
    const el = document.getElementById('content');
    el.innerHTML = 'loading...';

    fetch('/status')
      .then(response => response.json())
      .then(json => {
        el.innerHTML = '<pre>' + json + '</pre>';
      })
      .catch(err => {
        el.innerHTML = 'Error loading page: ' + err;
      })
  </script>
</body>
</html>
)";
