from pystrich.code128 import Code128Encoder
barcode = "RD642423939CN"
encoder = Code128Encoder(barcode)
encoder.save("bc.png")