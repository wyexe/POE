# -*- mode: python -*-

block_cipher = None


a = Analysis(['LFConsole.py', 'MouseAction.py', 'PicMatch.py', 'WeGame.py'],
             pathex=['D:\\Visual Studio 2010\\Projects\\ProjLFZL\\LFConsole'],
             binaries=[],
             datas=[],
             hiddenimports=[],
             hookspath=[],
             runtime_hooks=[],
             excludes=[],
             win_no_prefer_redirects=False,
             win_private_assemblies=False,
             cipher=block_cipher)
pyz = PYZ(a.pure, a.zipped_data,
             cipher=block_cipher)
exe = EXE(pyz,
          a.scripts,
          a.binaries,
          a.zipfiles,
          a.datas,
          name='LFConsole',
          debug=False,
          strip=False,
          upx=True,
          runtime_tmpdir=None,
          console=True )
