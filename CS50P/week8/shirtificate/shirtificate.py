from fpdf import FPDF

user_input = input("Name: ")

pdf = FPDF(orientation="P", unit="mm", format="A4")
pdf.add_page()
pdf.set_margin(0)
pdf.set_font("helvetica", "", 50)
pdf.cell(100, 50, "CS50 Shirtificate", center=True, align="C", new_y="NEXT")
pdf.image("shirtificate.png", x=10, w=(pdf.epw * 0.9), h=(pdf.epw * 0.9), keep_aspect_ratio=True)
pdf.set_font("helvetica", "B", 20)
pdf.set_text_color(255,255,255)
pdf.cell(0, -250, f"{user_input} took CS50", center=True, align="C", new_y="NEXT")
pdf.output("shirtificate.pdf")