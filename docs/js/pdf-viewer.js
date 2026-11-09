/* ============================================================
   pdf-viewer.js — Lightweight PDF viewer using PDF.js from CDN
   ============================================================ */

const PDF_JS_CDN = 'https://cdnjs.cloudflare.com/ajax/libs/pdf.js/4.4.168/pdf.min.mjs';
const PDF_JS_WORKER_CDN = 'https://cdnjs.cloudflare.com/ajax/libs/pdf.js/4.4.168/pdf.worker.min.mjs';

let pdfDoc = null;
let currentPage = 1;
let currentScale = 1.3;

async function loadPdfViewer(pdfUrl) {
  const container = document.getElementById('pdf-canvas-container');
  const pageInfo  = document.getElementById('pdf-page-info');
  if (!container) return;

  // Show loading
  container.innerHTML = `
    <div class="pdf-placeholder">
      <svg viewBox="0 0 24 24" fill="currentColor"><path d="M12 2C6.48 2 2 6.48 2 12s4.48 10 10 10 10-4.48 10-10S17.52 2 12 2zm-1 17.93c-3.95-.49-7-3.85-7-7.93 0-.62.08-1.21.21-1.79L9 15v1c0 1.1.9 2 2 2v1.93zm6.9-2.54c-.26-.81-1-1.39-1.9-1.39h-1v-3c0-.55-.45-1-1-1H8v-2h2c.55 0 1-.45 1-1V7h2c1.1 0 2-.9 2-2v-.41c2.93 1.19 5 4.06 5 7.41 0 2.08-.8 3.97-2.1 5.39z"/></svg>
      <p>Loading PDF…</p>
    </div>`;

  try {
    const pdfjsLib = await import(PDF_JS_CDN);
    pdfjsLib.GlobalWorkerOptions.workerSrc = PDF_JS_WORKER_CDN;

    pdfDoc = await pdfjsLib.getDocument(pdfUrl).promise;
    currentPage = 1;
    renderPage();
  } catch (err) {
    console.error('PDF load failed:', err);
    container.innerHTML = `
      <div class="pdf-placeholder">
        <svg viewBox="0 0 24 24" fill="currentColor"><path d="M14 2H6c-1.1 0-2 .9-2 2v16c0 1.1.9 2 2 2h12c1.1 0 2-.9 2-2V8l-6-6zm-1 9h-2v2H9v-2H7V9h2V7h2v2h2v2zm-1-7 5.5 5.5H12V4z"/></svg>
        <p>Chapter summary PDF not yet available.</p>
        <p style="font-size:.78rem">The summary PDF will appear here once created.</p>
      </div>`;
  }
}

async function renderPage() {
  if (!pdfDoc) return;
  const container = document.getElementById('pdf-canvas-container');
  const pageInfo  = document.getElementById('pdf-page-info');

  const page = await pdfDoc.getPage(currentPage);
  const viewport = page.getViewport({ scale: currentScale });

  // Create canvas
  const canvas = document.createElement('canvas');
  const ctx = canvas.getContext('2d');
  canvas.width = viewport.width;
  canvas.height = viewport.height;

  container.innerHTML = '';
  container.appendChild(canvas);

  await page.render({ canvasContext: ctx, viewport }).promise;

  if (pageInfo) {
    pageInfo.textContent = `${currentPage} / ${pdfDoc.numPages}`;
  }

  // Update button states
  const prevBtn = document.getElementById('pdf-prev');
  const nextBtn = document.getElementById('pdf-next');
  if (prevBtn) prevBtn.disabled = currentPage <= 1;
  if (nextBtn) nextBtn.disabled = currentPage >= pdfDoc.numPages;
}

function pdfPrev() {
  if (currentPage > 1) { currentPage--; renderPage(); }
}

function pdfNext() {
  if (pdfDoc && currentPage < pdfDoc.numPages) { currentPage++; renderPage(); }
}

function pdfZoomIn() {
  currentScale = Math.min(currentScale + 0.2, 3);
  renderPage();
}

function pdfZoomOut() {
  currentScale = Math.max(currentScale - 0.2, 0.5);
  renderPage();
}
