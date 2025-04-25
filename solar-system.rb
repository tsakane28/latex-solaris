class SolarSystem < Formula
  desc "Solar system simulation using OpenGL"
  homepage "https://github.com/yourname/latex-solaris"
  url "https://github.com/yourname/latex-solaris/archive/refs/tags/v1.0.0.tar.gz"
  sha256 "REPLACE_WITH_ACTUAL_SHA256_AFTER_RELEASE"
  license "MIT"
  
  depends_on "freeglut"
  
  def install
    system "make"
    bin.install "solar-system"
  end
  
  test do
    system "#{bin}/solar-system", "--version"
  end
end 