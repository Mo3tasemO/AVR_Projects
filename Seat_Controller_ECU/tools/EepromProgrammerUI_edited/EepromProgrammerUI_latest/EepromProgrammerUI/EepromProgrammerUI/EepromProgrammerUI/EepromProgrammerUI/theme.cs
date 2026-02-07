using System;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace EepromProgrammerUI
{
    // Small palette type (rename if you already have ThemePalette elsewhere)
    public sealed class UiPalette
    {
        public Color Bg, Surface, SurfaceAlt, Text, MutedText, Border;
        public Color InputBg, InputText, LogBg, LogFg;
        public Font UiFont, MonoFont;

        public UiPalette(Color bg, Color surface, Color surfaceAlt, Color text, Color mutedText,
                         Color border, Color inputBg, Color inputText, Color logBg, Color logFg,
                         Font uiFont, Font monoFont)
        {
            Bg = bg; Surface = surface; SurfaceAlt = surfaceAlt; Text = text; MutedText = mutedText;
            Border = border; InputBg = inputBg; InputText = inputText; LogBg = logBg; LogFg = logFg;
            UiFont = uiFont; MonoFont = monoFont;
        }
    }

    public static class UiPalettes
    {
        // Eye-friendly dark
        public static readonly UiPalette Dark = new UiPalette(
            bg: Color.FromArgb(22, 26, 33),
            surface: Color.FromArgb(30, 36, 46),
            surfaceAlt: Color.FromArgb(38, 45, 58),
            text: Color.FromArgb(232, 236, 241),
            mutedText: Color.FromArgb(165, 174, 188),
            border: Color.FromArgb(70, 84, 100),
            inputBg: Color.FromArgb(26, 31, 40),
            inputText: Color.FromArgb(232, 236, 241),
            logBg: Color.FromArgb(10, 12, 18),
            logFg: Color.FromArgb(176, 228, 176),
            uiFont: new Font("Segoe UI", 9f, FontStyle.Regular),
            monoFont: new Font("Consolas", 10f, FontStyle.Regular)
        );

        // Soft light
        public static readonly UiPalette Light = new UiPalette(
            bg: Color.FromArgb(245, 247, 250),
            surface: Color.White,
            surfaceAlt: Color.FromArgb(248, 249, 251),
            text: Color.FromArgb(31, 41, 55),
            mutedText: Color.FromArgb(108, 117, 125),
            border: Color.FromArgb(210, 214, 220),
            inputBg: Color.White,
            inputText: Color.FromArgb(31, 41, 55),
            logBg: Color.White,
            logFg: Color.FromArgb(31, 41, 55),
            uiFont: new Font("Segoe UI", 9f, FontStyle.Regular),
            monoFont: new Font("Consolas", 10f, FontStyle.Regular)
        );
    }

    public static class ThemeStyler
    {
        // Optional: make title bar dark on Win10/11 when using the dark palette
        [DllImport("dwmapi.dll")]
        private static extern int DwmSetWindowAttribute(IntPtr hwnd, int attr, ref int attrValue, int attrSize);
        private const int DWMWA_USE_IMMERSIVE_DARK_MODE = 20;

        /// <summary>
        /// Apply colors/fonts WITHOUT changing control sizes, positions, Dock/Anchor.
        /// </summary>
        public static void ApplyNoLayout(Form form, UiPalette p, bool darkTitleBar = true)
        {
            if (form == null || p == null) return;

            form.SuspendLayout();

            // Set form colors; DO NOT touch size/dock/anchor
            form.BackColor = p.Bg;
            form.ForeColor = p.Text;
            // Keep default font for labels to avoid AutoSize reflow
            // You can set a global UI font if all labels are fixed-size:
            // form.Font = p.UiFont;

            if (darkTitleBar && ReferenceEquals(p, UiPalettes.Dark))
            {
                try { int use = 1; DwmSetWindowAttribute(form.Handle, DWMWA_USE_IMMERSIVE_DARK_MODE, ref use, sizeof(int)); }
                catch { /* ignore if not supported */ }
            }

            ApplyRecursive(form, p);

            form.ResumeLayout(performLayout: false); // no layout recalculation
        }

        private static void ApplyRecursive(Control c, UiPalette p)
        {
            // snapshot geometry + autosize, style, then restore geometry
            var loc = c.Location;
            var size = c.Size;
            var auto = c.AutoSize;

            StyleControl(c, p);

            // Restore exactly as before
            c.AutoSize = false;               // temporarily force so Size applies
            c.Location = loc;
            c.Size = size;
            c.AutoSize = auto;                // restore original AutoSize

            // Children
            foreach (Control child in c.Controls)
                ApplyRecursive(child, p);
        }

        private static void StyleControl(Control c, UiPalette p)
        {
            // Default foreground
            c.ForeColor = p.Text;

            switch (c)
            {
                case GroupBox gb:
                    gb.BackColor = p.Surface;
                    gb.ForeColor = p.MutedText;            // softer label
                    gb.FlatStyle = FlatStyle.Standard;
                    break;

                case Panel pnl:
                    pnl.BackColor = p.Surface;
                    break;

                case TabControl tc:
                    tc.BackColor = p.Surface;
                    tc.ForeColor = p.Text;
                    foreach (TabPage tp in tc.TabPages)
                    {
                        tp.BackColor = p.Surface;
                        tp.ForeColor = p.Text;
                    }
                    break;

                case Button btn:
                    btn.UseVisualStyleBackColor = false;
                    btn.FlatStyle = FlatStyle.Flat;
                    btn.BackColor = p.SurfaceAlt;
                    btn.ForeColor = p.Text;
                    btn.FlatAppearance.BorderColor = p.Border;
                    btn.FlatAppearance.BorderSize = 1;
                    // do NOT change AutoSize/MinimumSize/Size
                    break;

                case TextBox tb:
                    tb.BackColor = p.InputBg;
                    tb.ForeColor = p.InputText;
                    tb.BorderStyle = BorderStyle.FixedSingle;
                    // keep tb.Font to avoid size changes; comment next line in if safe:
                    // tb.Font = p.UiFont;
                    break;

                case MaskedTextBox mtb:
                    mtb.BackColor = p.InputBg;
                    mtb.ForeColor = p.InputText;
                    mtb.BorderStyle = BorderStyle.FixedSingle;
                    break;

                case ComboBox cb:
                    cb.BackColor = p.InputBg;
                    cb.ForeColor = p.InputText;
                    cb.FlatStyle = FlatStyle.Flat;
                    break;

                case RichTextBox rtb:
                    rtb.BackColor = p.LogBg;
                    rtb.ForeColor = p.LogFg;
                    // Monospace improves readability; size remains unchanged
                    try { rtb.Font = p.MonoFont; } catch { }
                    rtb.BorderStyle = BorderStyle.FixedSingle;
                    rtb.WordWrap = false;
                    break;

                case Label lbl:
                    // Only color change; avoid font change because many labels are AutoSize
                    lbl.ForeColor = p.Text;
                    break;

                default:
                    // Keep defaults; only apply text color for readability
                    c.ForeColor = p.Text;
                    break;
            }
        }
    }
}
