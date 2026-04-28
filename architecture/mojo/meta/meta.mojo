# meta/meta.mojo

trait FaustMeta:
    @always_inline
    def declare(mut meta, var key: String, var val: String) -> None: pass
