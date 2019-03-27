module Builders
  class Vagrant < Builder
    TYPE = 'vagrant'

    def output_dir
      @scroll.artifact_dir
    end

    def inject(builder_def)
      @inject ||= builder_def
        .merge(
          'output_dir' => output_dir.to_s,
          'skip_add' => false,
        )
        .freeze
    end

    def artifact(_)
      @artifact ||= (output_dir / 'package.box')
    end
  end
end
