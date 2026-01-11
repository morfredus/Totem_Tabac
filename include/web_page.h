#ifndef WEB_PAGE_H
#define WEB_PAGE_H


#include <Arduino.h>
#include "modes.h"

inline String renderWebPage() {
    String html;
    html += "<!DOCTYPE html>\n";
    html += "<html lang=\"fr\">\n";
    html += "<head>\n";
    html += "<meta charset=\"UTF-8\">\n";
    html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    html += "<title>🎰 Totem Tabac</title>\n";
    html += "<style>\n";
    html += "@import url('https://fonts.googleapis.com/css2?family=Poppins:wght@400;600;700&display=swap');";
    html += "*{margin:0;padding:0;box-sizing:border-box;}";
    html += "body{font-family:'Poppins',sans-serif;background:linear-gradient(135deg,#667eea 0%,#764ba2 50%,#f093fb 100%);background-attachment:fixed;color:#fff;min-height:100vh;padding-bottom:40px;}";
    html += "@keyframes glow{0%,100%{box-shadow:0 0 20px rgba(255,215,0,0.3);}50%{box-shadow:0 0 40px rgba(255,215,0,0.8),0 0 60px rgba(255,215,0,0.4);}}";
    html += "@keyframes float{0%,100%{transform:translateY(0);}50%{transform:translateY(-10px);}}";
    html += "@keyframes pulse{0%,100%{transform:scale(1);}50%{transform:scale(1.05);}}";
    html += ".header{background:linear-gradient(135deg,rgba(255,255,255,0.1),rgba(255,255,255,0.05));backdrop-filter:blur(10px);padding:30px 20px;text-align:center;box-shadow:0 8px 32px rgba(0,0,0,0.1);border-bottom:2px solid rgba(255,255,255,0.2);margin-bottom:30px;}";
    html += ".header h1{margin:0;font-size:3em;font-weight:700;background:linear-gradient(45deg,#ffd700,#ff6b6b,#4ecdc4,#ffd700);background-size:300%;-webkit-background-clip:text;-webkit-text-fill-color:transparent;animation:glow 2s ease-in-out infinite,pulse 3s ease-in-out infinite;text-shadow:0 0 30px rgba(255,215,0,0.5);}";
    html += ".version,.ip{font-size:0.95em;opacity:.85;margin-top:8px;font-weight:500;}";
    html += ".container{max-width:1000px;margin:0 auto;padding:20px;}";
    html += ".param-card{background:linear-gradient(135deg,rgba(255,255,255,0.15),rgba(255,255,255,0.08));backdrop-filter:blur(15px);border-radius:20px;padding:24px;margin-bottom:30px;box-shadow:0 8px 32px rgba(0,0,0,0.15),inset 0 1px 0 rgba(255,255,255,0.2);border:1px solid rgba(255,255,255,0.18);transition:.3s;}";
    html += ".param-card:hover{transform:translateY(-5px);box-shadow:0 12px 40px rgba(0,0,0,0.2);}";
    html += ".param-title{font-size:1.3em;font-weight:700;margin-bottom:16px;color:#fff;text-shadow:0 2px 10px rgba(0,0,0,0.2);}";
    html += ".param-row{display:flex;align-items:center;gap:20px;margin-bottom:14px;flex-wrap:wrap;}";
    html += ".param-label{min-width:180px;font-weight:600;}";
    html += ".param-radio{margin-right:8px;width:20px;height:20px;cursor:pointer;}";
    html += ".param-slider{flex:1;min-width:200px;height:8px;-webkit-appearance:none;background:rgba(255,255,255,0.3);border-radius:10px;outline:none;}";
    html += ".param-slider::-webkit-slider-thumb{-webkit-appearance:none;width:24px;height:24px;background:linear-gradient(135deg,#ffd700,#ff6b6b);border-radius:50%;cursor:pointer;box-shadow:0 2px 10px rgba(0,0,0,0.3);transition:.2s;}";
    html += ".param-slider::-webkit-slider-thumb:hover{transform:scale(1.2);box-shadow:0 4px 20px rgba(255,215,0,0.6);}";
    html += "h2{font-size:1.8em;font-weight:700;margin:40px 0 20px 0;text-align:center;text-shadow:0 0 20px rgba(255,255,255,0.4);animation:float 3s ease-in-out infinite;}";
    html += ".grid{display:grid;grid-template-columns:repeat(auto-fit,minmax(160px,1fr));gap:18px;margin-bottom:24px;}";
    html += ".btn{background:linear-gradient(135deg,rgba(255,255,255,0.2),rgba(255,255,255,0.1));backdrop-filter:blur(10px);border-radius:15px;padding:22px 16px;text-align:center;font-size:1.1em;font-weight:600;cursor:pointer;transition:all .3s cubic-bezier(0.4,0,0.2,1);box-shadow:0 4px 15px rgba(0,0,0,0.1);border:2px solid rgba(255,255,255,0.2);position:relative;overflow:hidden;}";
    html += ".btn::before{content:'';position:absolute;top:0;left:-100%;width:100%;height:100%;background:linear-gradient(90deg,transparent,rgba(255,255,255,0.3),transparent);transition:0.5s;}";
    html += ".btn:hover::before{left:100%;}";
    html += ".btn:hover{transform:translateY(-5px) scale(1.05);box-shadow:0 8px 25px rgba(255,215,0,0.3);border-color:#ffd700;}";
    html += ".btn.selected{background:linear-gradient(135deg,#ffd700,#ffed4e);color:#222;font-weight:700;box-shadow:0 8px 30px rgba(255,215,0,0.6);border-color:#ffd700;animation:glow 2s ease-in-out infinite;}";
    html += ".submode-zone{margin-top:16px;margin-bottom:16px;text-align:center;min-height:60px;display:flex;align-items:center;justify-content:center;}";
    html += ".submode-btn{display:inline-block;background:linear-gradient(135deg,rgba(78,205,196,0.3),rgba(78,205,196,0.15));backdrop-filter:blur(10px);border-radius:12px;padding:16px 32px;font-size:1.05em;font-weight:600;cursor:pointer;transition:.3s;box-shadow:0 4px 15px rgba(0,0,0,0.15);border:2px solid rgba(78,205,196,0.5);color:#fff;}";
    html += ".submode-btn:hover{transform:scale(1.05);box-shadow:0 6px 25px rgba(78,205,196,0.5);border-color:#4ecdc4;background:linear-gradient(135deg,rgba(78,205,196,0.5),rgba(78,205,196,0.3));}";
    html += ".color-palette{display:flex;justify-content:center;align-items:center;flex-wrap:wrap;padding:20px;gap:16px;}";
    html += ".color-dot{width:60px;height:60px;border-radius:50%;cursor:pointer;border:4px solid rgba(255,255,255,0.3);transition:all .3s ease;box-shadow:0 4px 15px rgba(0,0,0,0.3);position:relative;}";
    html += ".color-dot::after{content:'✓';position:absolute;top:50%;left:50%;transform:translate(-50%,-50%) scale(0);font-size:30px;color:#fff;text-shadow:0 2px 5px rgba(0,0,0,0.5);transition:.3s;}";
    html += ".color-dot:hover{transform:scale(1.25) rotate(10deg);box-shadow:0 8px 30px rgba(255,215,0,0.6);border-color:#ffd700;}";
    html += ".color-dot.active::after{transform:translate(-50%,-50%) scale(1);}";
    html += "@media(max-width:700px){.container{padding:12px;}.param-row{flex-direction:column;align-items:flex-start;}.header h1{font-size:2.2em;}.grid{grid-template-columns:repeat(auto-fit,minmax(140px,1fr));gap:12px;}}";
    html += "</style>\n";
    html += "</head>\n";
    html += "<body>\n";
    html += "<div class=\"header\">\n";
    html += "<h1>🎰 TOTEM TABAC 🎰</h1>\n";
    html += "<div class=\"version\">✨ Version " PROJECT_VERSION " | 📡 ";
    html += getCurrentIP();
    html += "</div>\n";
    html += "</div>\n";
    html += "<div class=\"container\">\n";
    

    // Modes doux
    html += "<h2>🌿 Modes doux</h2><div class=\"grid\">\n";
    for(int i=0;i<=5;i++){
        html += "<div class=\"btn";
        if(currentMode==i) html += " selected";
        html += "";
        switch(i){
            case 0: html += " data-mode=\"0\" onclick='setMode(0)'>Ambiance</div>"; break;
            case 1: html += " data-mode=\"1\" onclick='setMode(1)'>Vague</div>"; break;
            case 2: html += " data-mode=\"2\" onclick='setMode(2)'>Arc-en-ciel</div>"; break;
            case 3: html += " data-mode=\"3\" onclick='setMode(3)'>Pulse Vert</div>"; break;
            case 4: html += " data-mode=\"4\" onclick='setMode(4)'>Pulse Jaune</div>"; break;
            case 5: html += " data-mode=\"5\" onclick='setMode(5)'>Pulse Rouge</div>"; break;
        }
    }
    html += "</div>\n";
    // Zone sous-mode pour modes doux
    html += "<div id='submode-doux' class='submode-zone'></div>\n";

    // Modes dynamiques
    html += "<h2>🔥 Modes dynamiques</h2><div class=\"grid\">\n";
    for(int i=6;i<=11;i++){
        html += "<div class=\"btn";
        if(currentMode==i) html += " selected";
        html += "";
        switch(i){
            case 6: html += " data-mode=\"6\" onclick='setMode(6)'>Rush</div>"; break;
            case 7: html += " data-mode=\"7\" onclick='setMode(7)'>K2000</div>"; break;
            case 8: html += " data-mode=\"8\" onclick='setMode(8)'>Jackpot</div>"; break;
            case 9: html += " data-mode=\"9\" onclick='setMode(9)'>FDJ Winner</div>"; break;
            case 10: html += " data-mode=\"10\" onclick='setMode(10)'>Gagnant</div>"; break;
            case 11: html += " data-mode=\"11\" onclick='setMode(11)'>Perdant</div>"; break;
        }
    }
    html += "</div>\n";
    // Zone sous-mode pour modes dynamiques
    html += "<div id='submode-dyn' class='submode-zone'></div>\n";

    // Utilitaires
    html += "<h2>🧱 Utilitaires</h2><div class=\"grid\">\n";
    for(int i=12;i<=16;i++){
        html += "<div class=\"btn";
        if(currentMode==i) html += " selected";
        html += "";
        switch(i){
            case 12: html += " data-mode=\"12\" onclick='setMode(12)'>Ouverture</div>"; break;
            case 13: html += " data-mode=\"13\" onclick='setMode(13)'>Fermeture</div>"; break;
            case 14: html += " data-mode=\"14\" onclick='setMode(14)'>Pause café</div>"; break;
            case 15: html += " data-mode=\"15\" onclick='setMode(15)'>Maintenance</div>"; break;
            case 16: html += " data-mode=\"16\" onclick='setMode(16)'>Humeur du Patron</div>"; break;
        }
    }
    html += "</div>\n";
    html += "<div id='submode-util' class='submode-zone'></div>\n";

    // Humeur du Patron
    html += "<h2>😎 Humeur du Patron 🎨</h2><div class=\"color-palette\">";
    html += "<span class=\"color-dot\" style=\"background:#22c55e;\" onclick=\"setHumeur(0)\" title=\"Vert - Tout va bien\"></span>";
    html += "<span class=\"color-dot\" style=\"background:#facc15;\" onclick=\"setHumeur(1)\" title=\"Jaune - Ça va\"></span>";
    html += "<span class=\"color-dot\" style=\"background:#ef4444;\" onclick=\"setHumeur(2)\" title=\"Rouge - Attention\"></span>";
    html += "<span class=\"color-dot\" style=\"background:#3b82f6;\" onclick=\"setHumeur(3)\" title=\"Bleu - Calme\"></span>";
    html += "<span class=\"color-dot\" style=\"background:#a855f7;\" onclick=\"setHumeur(4)\" title=\"Violet - Créatif\"></span>";
    html += "<span class=\"color-dot\" style=\"background:#ffffff;\" onclick=\"setHumeur(5)\" title=\"Blanc - Neutre\"></span>";
    html += "</div>\n";


    // Paramètres déplacés en fin et renommés
    html += "<div class=\"param-card\">\n";
    html += "<div class=\"param-title\">Utilitaires</div>\n";
    html += "<div class=\"param-row\">\n";
    html += "<span class=\"param-label\">Système d'affichage :</span>\n";
    html += "<label><input class=\"param-radio\" type='radio' name='display' value='0' ";
    if(getDisplayType()==DISPLAY_PWM) html += "checked ";
    html += "onclick='setDisplay(0)'> PWM (modules classiques)</label>\n";
    html += "<label><input class=\"param-radio\" type='radio' name='display' value='1' ";
    if(getDisplayType()==DISPLAY_MATRIX) html += "checked ";
    html += "onclick='setDisplay(1)'> Matrice NeoPixel 8x8</label>\n";
    html += "</div>\n";
    html += "<div class=\"param-row param-bright\" id=\"brightness-row\" style=\"display:";
    html += (getDisplayType()==DISPLAY_MATRIX?"flex":"none");
    html += ";\">\n";
    html += "<span class=\"param-label\">Luminosité matrice :</span>\n";
    html += "<input id=\"brightness-slider\" class=\"param-slider\" type='range' min='0' max='255' value='";
    html += String(getMatrixBrightness ? getMatrixBrightness() : 128);
    html += "' oninput='setBrightness(this.value)'>\n";
    html += "<span id=\"brightness-value\">";
    html += String(getMatrixBrightness ? getMatrixBrightness() : 128);
    html += "</span></div>\n";
    html += "<div class=\"param-row\">\n";
    html += "<span class=\"param-label\">🔄 Mise à jour OTA :</span>\n";
    html += "<div class=\"submode-btn\" onclick=\"window.open('/update','_blank')\">🚀 Ouvrir page de mise à jour</div>\n";
    html += "</div>\n";
    html += "</div>\n";

    html += "</div>\n"; // container

    // JS pour sous-modes dynamiques
    html += "<script>\n";
    html += "let currentMode = 0;\n";
    html += "let currentSub = 0;\n";
    html += "function fetchStatusAndUpdateSubmode() {\n";
    html += "  fetch('/status').then(r=>r.json()).then(data=>{\n";
    html += "    currentMode = data.mode;\n";
    html += "    currentSub = data.sub;\n";
    html += "    updateSubmodeUI();\n";
    html += "  });\n";
    html += "}\n";
    html += "function updateSubmodeUI() {\n";
    html += "  let mode = currentMode;\n";
    html += "  let sub = currentSub;\n";
    html += "  let submodeDoux = '';\n";
    html += "  let submodeDyn = '';\n";
    html += "  let submodeUtil = '';\n";
    html += "  // Modes doux (inclut Vague)\n";
    html += "  if([1,2,3,4,5].includes(mode)) {\n";
    html += "    submodeDoux = `<div class='submode-btn' onclick='nextSubMode()'>🎨 Sous-mode : <strong>${subModeLabel(mode,sub)}</strong></div>`;\n";
    html += "  }\n";
    html += "  document.getElementById('submode-doux').innerHTML = submodeDoux;\n";
    html += "  // Modes dynamiques\n";
    html += "  if([7,8].includes(mode)) {\n";
    html += "    submodeDyn = `<div class='submode-btn' onclick='nextSubMode()'>⚡ Sous-mode : <strong>${subModeLabel(mode,sub)}</strong></div>`;\n";
    html += "  }\n";
    html += "  document.getElementById('submode-dyn').innerHTML = submodeDyn;\n";
    html += "  // Utilitaires\n";
    html += "  if([16].includes(mode)) {\n";
    html += "    submodeUtil = `<div class='submode-btn' onclick='nextSubMode()'>🎨 Changer couleur</div>`;\n";
    html += "  }\n";
    html += "  document.getElementById('submode-util').innerHTML = submodeUtil;\n";
    html += "}\n";
    html += "function nextSubMode(){fetch('/submode').then(()=>{setTimeout(fetchStatusAndUpdateSubmode,200);});}\n";
    html += "function subModeLabel(mode,sub){\n";
    html += "  if([1,2,3,4,5,7,8].includes(mode)) return ['Lent','Moyen','Rapide'][sub%3];\n";
    html += "  return '';\n";
    html += "}\n";
    html += "document.addEventListener('DOMContentLoaded',fetchStatusAndUpdateSubmode);\n";
    html += "</script>\n";

    // JS embarqué pour l'interactivité AJAX (placé juste avant </body>)
    html += "<script>\n";
    html += "console.log('JS chargé');\n";
    html += "function setDisplay(val){\n";
    html += "  console.log('setDisplay',val);\n";
    html += "  fetch('/display?value=' + val).then(()=>{\n";
    html += "    document.querySelectorAll('.param-radio').forEach(r=>r.checked=false);\n";
    html += "    var sel = document.querySelector('.param-radio[value=\\\"' + val + '\\\"]'); if(sel) sel.checked=true;\n";
    html += "    if(val==1){document.getElementById('brightness-row').style.display='flex';}else{document.getElementById('brightness-row').style.display='none';}\n";
    html += "  });\n";
    html += "}\n";
    html += "function setBrightness(val){\n";
    html += "  console.log('setBrightness',val);\n";
    html += "  fetch('/brightness?value='+val);\n";
    html += "  document.getElementById('brightness-value').innerText=val;\n";
    html += "}\n";
    html += "function setMode(mode){\n";
    html += "  console.log('setMode',mode);\n";
    html += "  fetch('/mode?value='+mode).then(()=>{\n";
    html += "    document.querySelectorAll('.btn').forEach((b,i)=>{b.classList.remove('selected');if(i==mode)b.classList.add('selected');});\n";
    html += "    setTimeout(fetchStatusAndUpdateSubmode,200);\n";
    html += "  });\n";
    html += "}\n";
    html += "function setHumeur(val){\n";
    html += "  console.log('setHumeur',val);\n";
    html += "  fetch('/humeur?value='+val);\n";
    html += "}\n";
    html += "</script>\n";
    html += "</body>\n</html>\n";
    return html;
}

#endif // WEB_PAGE_H
