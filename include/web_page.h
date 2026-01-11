
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
    html += "<title>Totem Tabac</title>\n";
    html += "<style>\n";
    html += "body{font-family:sans-serif;background:#181c24;color:#fff;margin:0;padding:0;}";
    html += ".header{background:#222;padding:16px 0;text-align:center;}";
    html += ".header h1{margin:0;font-size:2.2em;letter-spacing:2px;}";
    html += ".version,.ip{font-size:1em;opacity:.7;}";
    html += ".container{max-width:900px;margin:24px auto;padding:16px;}";
    html += ".param-card{background:#23283a;border-radius:12px;padding:18px 20px 12px 20px;margin-bottom:24px;box-shadow:0 2px 8px #0003;}";
    html += ".param-title{font-size:1.2em;font-weight:bold;margin-bottom:10px;}";
    html += ".param-row{display:flex;align-items:center;gap:18px;margin-bottom:10px;}";
    html += ".param-label{min-width:140px;}";
    html += ".param-radio{margin-right:6px;}";
    html += ".param-slider{width:180px;}";
    html += ".grid{display:grid;grid-template-columns:repeat(auto-fit,minmax(140px,1fr));gap:14px;margin-bottom:18px;}";
    html += ".btn{background:#2d3748;border-radius:8px;padding:18px 0;text-align:center;font-size:1.1em;cursor:pointer;transition:.2s;box-shadow:0 2px 8px #0002;}";
    html += ".btn:hover{background:#4f5d75;color:#ffd700;transform:scale(1.05);}";
    html += ".btn.selected{background:#ffd700;color:#222;}";
    html += ".color-dot{display:inline-block;width:28px;height:28px;border-radius:50%;margin:0 4px;cursor:pointer;border:2px solid #fff3;transition:.2s;}";
    html += ".color-dot:hover{border:2px solid #ffd700;transform:scale(1.15);}";
    html += ".card{background:#23283a;border-radius:12px;padding:16px;margin-bottom:24px;}";
    html += "@media(max-width:600px){.container{padding:4px;}.param-row{flex-direction:column;align-items:flex-start;}}";
    html += "</style>\n";
    html += "</head>\n";
    html += "<body>\n";
    html += "<div class=\"header\">\n";
    html += "<h1>Totem Tabac</h1>\n";
    html += "<div class=\"version\">Version " PROJECT_VERSION "</div>\n";
    html += "<div class=\"ip\">IP : ";
    html += getCurrentIP();
    html += "</div>\n";
    html += "</div>\n";
    html += "<div class=\"container\">\n";
    // Paramètres
    html += "<div class=\"param-card\">\n";
    html += "<div class=\"param-title\">Paramètres d'affichage</div>\n";
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
    html += "<input id=\"brightness-slider\" class=\"param-slider\" type='range' min='10' max='255' value='";
    html += String(getMatrixBrightness ? getMatrixBrightness() : 128);
    html += "' oninput='setBrightness(this.value)'>\n";
    html += "<span id=\"brightness-value\">";
    html += String(getMatrixBrightness ? getMatrixBrightness() : 128);
    html += "</span></div>\n";
    html += "</div>\n";

    // Modes doux
    html += "<h2>🌿 Modes doux</h2><div class=\"grid\">\n";
    for(int i=0;i<=7;i++){
        html += "<div class=\"btn";
        if(currentMode==i) html += " selected";
        html += "";
        switch(i){
            case 0: html += " data-mode=\"0\" onclick='setMode(0)'>Zen</div>"; break;
            case 1: html += " data-mode=\"1\" onclick='setMode(1)'>Ambiance</div>"; break;
            case 2: html += " data-mode=\"2\" onclick='setMode(2)'>Vague</div>"; break;
            case 3: html += " data-mode=\"3\" onclick='setMode(3)'>Arc-en-ciel</div>"; break;
            case 4: html += " data-mode=\"4\" onclick='setMode(4)'>Arc-en-ciel Turbo</div>"; break;
            case 5: html += " data-mode=\"5\" onclick='setMode(5)'>Pulse Vert</div>"; break;
            case 6: html += " data-mode=\"6\" onclick='setMode(6)'>Pulse Jaune</div>"; break;
            case 7: html += " data-mode=\"7\" onclick='setMode(7)'>Pulse Rouge</div>"; break;
        }
    }
    html += "</div>\n";

    // Modes dynamiques
    html += "<h2>🔥 Modes dynamiques</h2><div class=\"grid\">\n";
    for(int i=8;i<=14;i++){
        html += "<div class=\"btn";
        if(currentMode==i) html += " selected";
        html += "";
        switch(i){
            case 8: html += " data-mode=\"8\" onclick='setMode(8)'>Rush</div>"; break;
            case 9: html += " data-mode=\"9\" onclick='setMode(9)'>K2000</div>"; break;
            case 10: html += " data-mode=\"10\" onclick='setMode(10)'>Disco</div>"; break;
            case 11: html += " data-mode=\"11\" onclick='setMode(11)'>Jackpot</div>"; break;
            case 12: html += " data-mode=\"12\" onclick='setMode(12)'>FDJ Winner</div>"; break;
            case 13: html += " data-mode=\"13\" onclick='setMode(13)'>Gagnant</div>"; break;
            case 14: html += " data-mode=\"14\" onclick='setMode(14)'>Perdant</div>"; break;
        }
    }
    html += "</div>\n";

    // Utilitaires
    html += "<h2>🧱 Utilitaires</h2><div class=\"grid\">\n";
    for(int i=15;i<=19;i++){
        html += "<div class=\"btn";
        if(currentMode==i) html += " selected";
        html += "";
        switch(i){
            case 15: html += " data-mode=\"15\" onclick='setMode(15)'>Ouverture</div>"; break;
            case 16: html += " data-mode=\"16\" onclick='setMode(16)'>Fermeture</div>"; break;
            case 17: html += " data-mode=\"17\" onclick='setMode(17)'>Pause café</div>"; break;
            case 18: html += " data-mode=\"18\" onclick='setMode(18)'>Maintenance</div>"; break;
            case 19: html += " data-mode=\"19\" onclick='setMode(19)'>Humeur du Patron</div>"; break;
        }
    }
    html += "</div>\n";

    // Humeur du Patron
    html += "<h2>😎 Humeur du Patron</h2><div style=\"display:flex;justify-content:center;gap:10px;\">";
    html += "<span class=\"color-dot\" style=\"background:#22c55e\" onclick=\"setHumeur(0)\"></span>";
    html += "<span class=\"color-dot\" style=\"background:#facc15\" onclick=\"setHumeur(1)\"></span>";
    html += "<span class=\"color-dot\" style=\"background:#ef4444\" onclick=\"setHumeur(2)\"></span>";
    html += "<span class=\"color-dot\" style=\"background:#3b82f6\" onclick=\"setHumeur(3)\"></span>";
    html += "<span class=\"color-dot\" style=\"background:#a855f7\" onclick=\"setHumeur(4)\"></span>";
    html += "<span class=\"color-dot\" style=\"background:#ffffff\" onclick=\"setHumeur(5)\"></span>";
    html += "</div>\n";


    html += "</div>\n"; // container

    // JS embarqué pour l'interactivité AJAX (placé juste avant </body>)
    html += "<script>\n";
    html += "console.log('JS chargé');\n";
    html += "function setDisplay(val){\n";
    html += "  console.log('setDisplay',val);\n";
        html += "  fetch('/display?value=' + val).then(()=>{\n";
    html += "    document.querySelectorAll('.param-radio').forEach(r=>r.checked=false);\n";
    html += "    var sel = document.querySelector('.param-radio[value=\"' + val + '\"]'); if(sel) sel.checked=true;\n";
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
