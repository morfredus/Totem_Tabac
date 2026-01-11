#ifndef OTA_PAGE_H
#define OTA_PAGE_H

#include <Arduino.h>

inline String renderOTAPage() {
    String html;
    html += "<!DOCTYPE html>\n";
    html += "<html lang=\"fr\">\n";
    html += "<head>\n";
    html += "<meta charset=\"UTF-8\">\n";
    html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    html += "<title>🚀 Mise à jour OTA - Totem Tabac</title>\n";
    html += "<style>\n";
    html += "@import url('https://fonts.googleapis.com/css2?family=Poppins:wght@400;600;700&display=swap');";
    html += "*{margin:0;padding:0;box-sizing:border-box;}";
    html += "body{font-family:'Poppins',sans-serif;background:linear-gradient(135deg,#667eea 0%,#764ba2 50%,#f093fb 100%);background-attachment:fixed;color:#fff;min-height:100vh;padding:40px 20px;}";
    html += "@keyframes glow{0%,100%{box-shadow:0 0 20px rgba(255,215,0,0.3);}50%{box-shadow:0 0 40px rgba(255,215,0,0.8),0 0 60px rgba(255,215,0,0.4);}}";
    html += "@keyframes pulse{0%,100%{transform:scale(1);}50%{transform:scale(1.05);}}";
    html += "@keyframes progressAnim{0%{background-position:0% 50%;}50%{background-position:100% 50%;}100%{background-position:0% 50%;}}";
    html += ".header{background:linear-gradient(135deg,rgba(255,255,255,0.1),rgba(255,255,255,0.05));backdrop-filter:blur(10px);padding:30px 20px;text-align:center;box-shadow:0 8px 32px rgba(0,0,0,0.1);border-radius:20px;border:1px solid rgba(255,255,255,0.2);margin-bottom:30px;}";
    html += ".header h1{margin:0;font-size:2.5em;font-weight:700;background:linear-gradient(45deg,#ffd700,#ff6b6b,#4ecdc4,#ffd700);background-size:300%;-webkit-background-clip:text;-webkit-text-fill-color:transparent;animation:glow 2s ease-in-out infinite;}";
    html += ".container{max-width:800px;margin:0 auto;}";
    html += ".card{background:linear-gradient(135deg,rgba(255,255,255,0.15),rgba(255,255,255,0.08));backdrop-filter:blur(15px);border-radius:20px;padding:30px;margin-bottom:25px;box-shadow:0 8px 32px rgba(0,0,0,0.15);border:1px solid rgba(255,255,255,0.18);}";
    html += ".card-title{font-size:1.5em;font-weight:700;margin-bottom:20px;color:#fff;text-shadow:0 2px 10px rgba(0,0,0,0.2);}";
    html += ".info-box{background:rgba(78,205,196,0.2);border-left:4px solid #4ecdc4;padding:15px;border-radius:10px;margin-bottom:20px;}";
    html += ".info-box h3{font-size:1.1em;margin-bottom:8px;color:#4ecdc4;}";
    html += ".info-box ul{margin-left:20px;line-height:1.8;}";
    html += ".file-input-wrapper{position:relative;overflow:hidden;display:inline-block;width:100%;margin-bottom:20px;}";
    html += ".file-input-label{display:block;background:linear-gradient(135deg,rgba(255,255,255,0.25),rgba(255,255,255,0.15));border:2px dashed rgba(255,255,255,0.4);border-radius:15px;padding:40px 20px;text-align:center;cursor:pointer;transition:all 0.3s;font-weight:600;font-size:1.1em;}";
    html += ".file-input-label:hover{border-color:#ffd700;background:linear-gradient(135deg,rgba(255,215,0,0.3),rgba(255,215,0,0.15));transform:translateY(-3px);}";
    html += ".file-input{display:none;}";
    html += ".selected-file{background:rgba(78,205,196,0.3);border:2px solid #4ecdc4;border-radius:10px;padding:15px;margin-bottom:20px;display:none;align-items:center;gap:10px;}";
    html += ".selected-file.show{display:flex;}";
    html += ".btn{background:linear-gradient(135deg,#4ecdc4,#44a08d);border:none;color:#fff;padding:18px 40px;font-size:1.2em;font-weight:700;border-radius:15px;cursor:pointer;transition:all 0.3s;box-shadow:0 4px 15px rgba(0,0,0,0.2);width:100%;margin-top:10px;}";
    html += ".btn:hover:not(:disabled){transform:translateY(-5px);box-shadow:0 8px 25px rgba(78,205,196,0.4);}";
    html += ".btn:disabled{opacity:0.5;cursor:not-allowed;}";
    html += ".progress-container{background:rgba(0,0,0,0.3);border-radius:15px;height:40px;margin-bottom:20px;overflow:hidden;display:none;}";
    html += ".progress-container.show{display:block;}";
    html += ".progress-bar{height:100%;background:linear-gradient(90deg,#4ecdc4,#44a08d,#4ecdc4);background-size:200% 100%;transition:width 0.3s;display:flex;align-items:center;justify-content:center;font-weight:700;font-size:1.1em;animation:progressAnim 2s linear infinite;}";
    html += ".message-zone{min-height:60px;margin-bottom:20px;padding:15px;border-radius:10px;display:none;}";
    html += ".message-zone.show{display:block;}";
    html += ".message-zone.error{background:rgba(239,68,68,0.3);border:2px solid #ef4444;}";
    html += ".message-zone.success{background:rgba(34,197,94,0.3);border:2px solid #22c55e;}";
    html += ".message-zone.info{background:rgba(59,130,246,0.3);border:2px solid #3b82f6;}";
    html += ".back-link{display:inline-block;background:linear-gradient(135deg,rgba(255,255,255,0.2),rgba(255,255,255,0.1));padding:15px 30px;border-radius:12px;color:#fff;text-decoration:none;font-weight:600;transition:0.3s;border:2px solid rgba(255,255,255,0.2);margin-top:20px;}";
    html += ".back-link:hover{background:linear-gradient(135deg,rgba(255,215,0,0.3),rgba(255,215,0,0.2));border-color:#ffd700;transform:translateY(-3px);}";
    html += "</style>\n";
    html += "</head>\n";
    html += "<body>\n";
    html += "<div class=\"container\">\n";
    
    // Header
    html += "<div class=\"header\">\n";
    html += "<h1>🚀 Mise à jour OTA</h1>\n";
    html += "<p style=\"margin-top:10px;opacity:0.9;\">Mise à jour sans fil du firmware</p>\n";
    html += "</div>\n";
    
    // Info Card
    html += "<div class=\"card\">\n";
    html += "<div class=\"card-title\">📋 Informations</div>\n";
    html += "<div class=\"info-box\">\n";
    html += "<h3>📦 Fichiers acceptés</h3>\n";
    html += "<ul>\n";
    html += "<li><strong>firmware.bin</strong> - Firmware principal (code compilé)</li>\n";
    html += "<li><strong>spiffs.bin</strong> - Système de fichiers (optionnel)</li>\n";
    html += "</ul>\n";
    html += "</div>\n";
    html += "<div class=\"info-box\">\n";
    html += "<h3>⚠️ Important</h3>\n";
    html += "<ul>\n";
    html += "<li>Ne débranchez pas l'ESP32 pendant la mise à jour</li>\n";
    html += "<li>Attendez le redémarrage automatique (environ 10 secondes)</li>\n";
    html += "<li>Les paramètres et animations sont conservés</li>\n";
    html += "</ul>\n";
    html += "</div>\n";
    html += "</div>\n";
    
    // Upload Card
    html += "<div class=\"card\">\n";
    html += "<div class=\"card-title\">📤 Téléverser le firmware</div>\n";
    
    // Message zone
    html += "<div id=\"messageZone\" class=\"message-zone\"></div>\n";
    
    // File input
    html += "<form id=\"uploadForm\" method=\"POST\" enctype=\"multipart/form-data\">\n";
    html += "<div class=\"file-input-wrapper\">\n";
    html += "<label for=\"fileInput\" class=\"file-input-label\" id=\"fileLabel\">\n";
    html += "📁 Cliquez pour sélectionner un fichier .bin\n";
    html += "</label>\n";
    html += "<input type=\"file\" id=\"fileInput\" name=\"update\" accept=\".bin\" class=\"file-input\">\n";
    html += "</div>\n";
    
    html += "<div id=\"selectedFile\" class=\"selected-file\">\n";
    html += "✅ <span id=\"fileName\"></span> (<span id=\"fileSize\"></span>)\n";
    html += "</div>\n";
    
    html += "<div id=\"progressContainer\" class=\"progress-container\">\n";
    html += "<div id=\"progressBar\" class=\"progress-bar\">0%</div>\n";
    html += "</div>\n";
    
    html += "<button type=\"button\" id=\"uploadBtn\" class=\"btn\" disabled onclick=\"startUpload()\">🚀 Démarrer la mise à jour</button>\n";
    html += "</form>\n";
    
    html += "<a href=\"/\" class=\"back-link\">← Retour à l'interface principale</a>\n";
    html += "</div>\n";
    
    html += "</div>\n"; // container
    
    // JavaScript
    html += "<script>\n";
    html += "const fileInput = document.getElementById('fileInput');\n";
    html += "const uploadBtn = document.getElementById('uploadBtn');\n";
    html += "const selectedFile = document.getElementById('selectedFile');\n";
    html += "const fileName = document.getElementById('fileName');\n";
    html += "const fileSize = document.getElementById('fileSize');\n";
    html += "const progressContainer = document.getElementById('progressContainer');\n";
    html += "const progressBar = document.getElementById('progressBar');\n";
    html += "const messageZone = document.getElementById('messageZone');\n";
    html += "const fileLabel = document.getElementById('fileLabel');\n";
    
    html += "function showMessage(msg, type) {\n";
    html += "  messageZone.textContent = msg;\n";
    html += "  messageZone.className = 'message-zone show ' + type;\n";
    html += "}\n";
    
    html += "function hideMessage() {\n";
    html += "  messageZone.className = 'message-zone';\n";
    html += "}\n";
    
    html += "function formatSize(bytes) {\n";
    html += "  if (bytes < 1024) return bytes + ' B';\n";
    html += "  if (bytes < 1048576) return (bytes / 1024).toFixed(2) + ' KB';\n";
    html += "  return (bytes / 1048576).toFixed(2) + ' MB';\n";
    html += "}\n";
    
    html += "fileInput.addEventListener('change', function() {\n";
    html += "  hideMessage();\n";
    html += "  if (this.files.length === 0) {\n";
    html += "    selectedFile.classList.remove('show');\n";
    html += "    uploadBtn.disabled = true;\n";
    html += "    fileLabel.textContent = '📁 Cliquez pour sélectionner un fichier .bin';\n";
    html += "    return;\n";
    html += "  }\n";
    html += "  const file = this.files[0];\n";
    html += "  if (!file.name.endsWith('.bin')) {\n";
    html += "    showMessage('❌ Erreur : Seuls les fichiers .bin sont acceptés', 'error');\n";
    html += "    this.value = '';\n";
    html += "    selectedFile.classList.remove('show');\n";
    html += "    uploadBtn.disabled = true;\n";
    html += "    return;\n";
    html += "  }\n";
    html += "  fileName.textContent = file.name;\n";
    html += "  fileSize.textContent = formatSize(file.size);\n";
    html += "  selectedFile.classList.add('show');\n";
    html += "  uploadBtn.disabled = false;\n";
    html += "  fileLabel.textContent = '📁 Fichier sélectionné - Cliquez pour changer';\n";
    html += "});\n";
    
    html += "function startUpload() {\n";
    html += "  if (fileInput.files.length === 0) {\n";
    html += "    showMessage('❌ Veuillez sélectionner un fichier', 'error');\n";
    html += "    return;\n";
    html += "  }\n";
    html += "  hideMessage();\n";
    html += "  uploadBtn.disabled = true;\n";
    html += "  fileInput.disabled = true;\n";
    html += "  progressContainer.classList.add('show');\n";
    html += "  showMessage('📤 Préparation de la mise à jour...', 'info');\n";
    
    html += "  const formData = new FormData();\n";
    html += "  formData.append('update', fileInput.files[0]);\n";
    
    html += "  const xhr = new XMLHttpRequest();\n";
    html += "  xhr.upload.addEventListener('progress', function(e) {\n";
    html += "    if (e.lengthComputable) {\n";
    html += "      const percent = Math.round((e.loaded / e.total) * 100);\n";
    html += "      progressBar.style.width = percent + '%';\n";
    html += "      progressBar.textContent = percent + '%';\n";
    html += "      showMessage('📤 Téléversement en cours : ' + percent + '%', 'info');\n";
    html += "    }\n";
    html += "  });\n";
    
    html += "  xhr.addEventListener('load', function() {\n";
    html += "    if (xhr.status === 200) {\n";
    html += "      progressBar.style.width = '100%';\n";
    html += "      progressBar.textContent = '100%';\n";
    html += "      showMessage('✅ Mise à jour réussie ! Redémarrage en cours...', 'success');\n";
    html += "      setTimeout(function() {\n";
    html += "        showMessage('🔄 Redirection vers l\\'interface principale...', 'info');\n";
    html += "        setTimeout(function() {\n";
    html += "          window.location.href = '/';\n";
    html += "        }, 3000);\n";
    html += "      }, 2000);\n";
    html += "    } else {\n";
    html += "      showMessage('❌ Erreur lors de la mise à jour : ' + xhr.statusText, 'error');\n";
    html += "      uploadBtn.disabled = false;\n";
    html += "      fileInput.disabled = false;\n";
    html += "    }\n";
    html += "  });\n";
    
    html += "  xhr.addEventListener('error', function() {\n";
    html += "    showMessage('❌ Erreur réseau lors de l\\'envoi du fichier', 'error');\n";
    html += "    uploadBtn.disabled = false;\n";
    html += "    fileInput.disabled = false;\n";
    html += "  });\n";
    
    html += "  xhr.open('POST', '/update');\n";
    html += "  xhr.send(formData);\n";
    html += "}\n";
    html += "</script>\n";
    
    html += "</body>\n</html>\n";
    return html;
}

#endif // OTA_PAGE_H
