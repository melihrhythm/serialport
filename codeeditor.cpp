#include <QtWidgets>
#include "codeeditor.h"

/**
 * @brief CodeEditor sınıfının yapıcı fonksiyonu.
 *
 * @param parent Üst widget.
 */
CodeEditor::CodeEditor(QWidget *parent) : QPlainTextEdit(parent)
{
    lineNumberArea = new LineNumberArea(this);

    // blockCountChanged, updateRequest ve cursorPositionChanged sinyallerini uygun slotlara bağlar
    connect(this, &CodeEditor::blockCountChanged, this, &CodeEditor::updateLineNumberAreaWidth);
    connect(this, &CodeEditor::updateRequest, this, &CodeEditor::updateLineNumberArea);
    connect(this, &CodeEditor::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine);

    // Satır numarası alanı genişliğini başlatmak için çağırır
    updateLineNumberAreaWidth(0);
}

/**
 * @brief Satır numarası alanının genişliğini döner.
 *
 * Bu fonksiyon, satır numaralarının genişliğini hesaplar ve döner.
 *
 * @return int Satır numarası alanı genişliği.
 */
int CodeEditor::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());

    while (max >= 10)
    {
        max /= 10;
        ++digits;
    }

    int space = 10 + fontMetrics().horizontalAdvance("  ") * digits;

    return space;
}

/**
 * @brief Satır numarası alanı genişliğini günceller.
 *
 * Bu fonksiyon, satır numarası alanı genişliğini günceller ve düzenleyici
 * alanının görünümünü ayarlar.
 *
 * @param newBlockCount Yeni blok sayısı.
 */
void CodeEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

/**
 * @brief Satır numarası alanını günceller.
 *
 * Bu fonksiyon, satır numarası alanını verilen dikdörtgen ve dikey kaydırma
 * değeri ile günceller.
 *
 * @param rect Güncellenecek alan.
 * @param dy Dikey kaydırma değeri.
 */
void CodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

/**
 * @brief Yeniden boyutlandırma olayını işler.
 *
 * Bu fonksiyon, düzenleyici yeniden boyutlandırıldığında satır numarası
 * alanını da yeniden boyutlandırır.
 *
 * @param e Yeniden boyutlandırma olayı.
 */
void CodeEditor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

/**
 * @brief Geçerli satırı vurgular.
 *
 * Bu fonksiyon, geçerli satırı vurgular. Eğer vurgulama etkinse, geçerli
 * satırı sarı renkle işaretler.
 */
void CodeEditor::highlightCurrentLine()
{
    if (isHighlightCurrentLineEnabled == true)
    {
        QList<QTextEdit::ExtraSelection> extraSelections;
        QTextEdit::ExtraSelection selection;
        QColor lineColor = QColor(Qt::yellow).lighter(160);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);

        setExtraSelections(extraSelections);
    }
}

/**
 * @brief Geçerli satırın vurgulanıp vurgulanmayacağını ayarlar.
 *
 * Bu fonksiyon, geçerli satırın vurgulanıp vurgulanmayacağını belirler.
 *
 * @param status Vurgulama durumu.
 */
void CodeEditor::setHighlightEnabled(bool status)
{
    isHighlightCurrentLineEnabled = status;
}

/**
 * @brief Satır numarası alanını boyar.
 *
 * Bu fonksiyon, satır numarası alanını verilen boyama olayı ile boyar.
 *
 * @param event Boyama olayı.
 */
void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int)blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int)blockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom())
    {
        if (block.isVisible() && bottom >= event->rect().top())
        {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(), Qt::AlignLeft, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int)blockBoundingRect(block).height();
        ++blockNumber;
    }
}
