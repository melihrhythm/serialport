#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>

QT_BEGIN_NAMESPACE
class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;
QT_END_NAMESPACE

class LineNumberArea;

/**
 * @brief CodeEditor sınıfı, QPlainTextEdit sınıfını genişleterek satır numaralarını gösterir
 * ve geçerli satırı vurgular.
 */
class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    /**
     * @brief CodeEditor yapıcı fonksiyonu.
     *
     * @param parent Üst widget.
     */
    CodeEditor(QWidget *parent = nullptr);

    /**
     * @brief Satır numarası alanını boyama işlevi.
     *
     * @param event Boyama olayı.
     */
    void lineNumberAreaPaintEvent(QPaintEvent *event);

    /**
     * @brief Satır numarası alanının genişliğini döner.
     *
     * @return int Satır numarası alanı genişliği.
     */
    int lineNumberAreaWidth();

    /**
     * @brief Geçerli satırın vurgulanıp vurgulanmayacağını ayarlar.
     *
     * @param status Vurgulama durumu.
     */
    void setHighlightEnabled(bool status);

protected:
    /**
     * @brief Yeniden boyutlandırma olayını işler.
     *
     * @param event Yeniden boyutlandırma olayı.
     */
    void resizeEvent(QResizeEvent *event) override;

private slots:
    /**
     * @brief Satır numarası alanı genişliğini günceller.
     *
     * @param newBlockCount Yeni blok sayısı.
     */
    void updateLineNumberAreaWidth(int newBlockCount);

    /**
     * @brief Geçerli satırı vurgular.
     */
    void highlightCurrentLine();

    /**
     * @brief Satır numarası alanını günceller.
     *
     * @param rect Güncellenecek alan.
     * @param dy Dikey kaydırma değeri.
     */
    void updateLineNumberArea(const QRect &rect, int dy);

private:
    QWidget *lineNumberArea; /**< Satır numarası alanı. */
    bool isHighlightCurrentLineEnabled = false; /**< Geçerli satırı vurgulama durumu. */
};

/**
 * @brief Satır numaralarını gösteren alan.
 */
class LineNumberArea : public QWidget
{
public:
    /**
     * @brief LineNumberArea yapıcı fonksiyonu.
     *
     * @param editor CodeEditor nesnesi.
     */
    LineNumberArea(CodeEditor *editor) : QWidget(editor)
    {
        codeEditor = editor;
    }

    /**
     * @brief Minimum genişliği döner.
     *
     * @return QSize Minimum genişlik.
     */
    QSize sizeHint() const override
    {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    /**
     * @brief Boyama olayını işler.
     *
     * @param event Boyama olayı.
     */
    void paintEvent(QPaintEvent *event) override
    {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    CodeEditor *codeEditor; /**< CodeEditor nesnesi. */
};

#endif // CODEEDITOR_H
